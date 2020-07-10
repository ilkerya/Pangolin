
//https://github.com/adafruit/Adafruit_SSD1306

// https://upload.wikimedia.org/wikipedia/commons/f/f8/Codepage-437.png
/*
#define OLED_CS    48// 13
#define OLED_RESET 46
#define OLED_DC    44// 12  // common 50
#define OLED_CLK   42 //13 // common  52
#define OLED_MOSI  40// 11 //common 51
*/


#define OLED_GND 46// 13
#define OLED_POWER 44// 13


#define OLED_CS    40// 13
#define OLED_RESET 38
#define OLED_DC    36// 12  // common 50
#define OLED_CLK   34 //13 // common  52
#define OLED_MOSI  32// 11 //common 51

/*
#define OLED_CS    A0
#define OLED_RESET A1
#define OLED_DC    A2
#define OLED_CLK   A3
#define OLED_MOSI  A4
*/


/*
#define OLED_GND 45// 13
#define OLED_POWER 43// 13
#define OLED_CS    39// 13
#define OLED_RESET 37
#define OLED_DC    35// 12  // common 50
#define OLED_CLK   33 //13 // common  52
#define OLED_MOSI  31// 11 //common 51
*/


   // pinMode(OLED_POWER, OUTPUT);
    //pinMode(8, OUTPUT);
    //pinMode(9, OUTPUT);
/*
#define OLED_CS    34// 13
#define OLED_RESET 36
#define OLED_DC    38// 12  // common 50
#define OLED_CLK   40 //13 // common  52
#define OLED_MOSI  42// 11 //common 51
*/




#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

  /*
 * In Adafruit_SSD1306.h
 * 1. uncomment #define SSD1306_128_64
2. comment #define SSD1306_128_32
3. comment #define SSD1306_96_16
In the example ssd1306_128x64_i2c
4. add #define SSD1306_LCDHEIGHT 64
 *
 */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//Adafruit_SSD1306 display(OLED_RESET);
//DISPLAY INITIALIZER
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
void Display_SwitchOff(){
      digitalWrite(OLED_POWER, LOW);       // turn on pullup resistors
      digitalWrite(OLED_GND, LOW);       // keep GND Level   
      Menu = MENU_NULL;       
}

void Display_ReInit(byte Timer){
    pinMode(OLED_GND, OUTPUT); 
    pinMode(OLED_POWER, OUTPUT);
    OLED_Timer = Timer; // 10 sec
    digitalWrite(OLED_POWER, HIGH);       // 
    digitalWrite(OLED_GND, LOW);       //  

    
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {  //    SSD1306_EXTERNALVCC
        Serial.println("SSD1306 allocation failed");
            //for(;;); // Don’t proceed, loop forever
    }
     Serial.println("Dsiplay ReInitilized");  
 //   display.clearDisplay();
 //   display.setTextSize(3);
 //   display.setTextColor(WHITE);  //0  white on black
 //    display.setTextColor(0);  //1     Black on white
    display.dim(1); // lower brightness 
 //   display.setCursor(0, 0);
 //   display.println();
//    display.println("DATALOG"); 
 //   display.display();
}

void DisplayInit(void){
    //-- DISPLAY INIT --//
    pinMode(OLED_GND, OUTPUT);
    digitalWrite(OLED_GND, LOW);       // keep GND Level           
    pinMode(OLED_POWER, OUTPUT);
    OLED_Timer = 40; // 20-> 10 sec
    digitalWrite(OLED_POWER, HIGH);       // turn on pullup resistors
    
    Serial.println("Display Initing");
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {  //  SSD1306_EXTERNALVCC
        Serial.println("SSD1306 allocation failed");
  
     // for(;;); // Don’t proceed, loop forever
      }
       display.dim(1); // lower brightness 
   // display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);  //0  white on black
 //    display.setTextColor(0);  //1     Black on white
    display.setCursor(0, 0);
    display.println();
    display.println("DATALOG"); 
      display.display();
  //    delay(250);
     // Adafruit_SSD1306::dim  ( 1 ) //1 == lower brightness // 0 == full brightness
      //display.dim       
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
 // delay(2000);
}

void SDcard_Info(){
            if(SDCard.Status = SD1_TYPE){
            display.print("SD1 ");display.print(SD_Volume);display.print("Gb"); // 4+5+2 = 11
            }
          else if(SDCard.Status = SD2_TYPE){
            display.print("SD2 ");display.print(SD_Volume);display.print("Gb");
            } 
          else if(SDCard.Status = SDHC_TYPE){
            display.print("SDH ");display.print(SD_Volume);display.print("Gb");
           } 
}

void SDCard_or_File(){
    switch(DisplayValueTimer){
      case 0:case 2:     
          SDcard_Info();
         break;
         case 1:case 3: 
           //display.print("File ");
           display.print(LOG_FILE); //10
           display.print(' '); //1
         break;
         default:
         break;  
    }      
}


void ShowLogTime(){
      String DispSample="";
      switch(SampleTime){
       case TASK_500MSEC:DispSample = "0.5Sec"; //5 
          break;        
        case TASK_1SEC : DispSample = "  1Sec";//5
          break; 
        case TASK_2SEC : DispSample = "  2Sec";
          break;        
        case TASK_5SEC : DispSample = "  5Sec";
          break;  
        case TASK_10SEC :DispSample = " 10Sec";
          break; 
        case TASK_20SEC :DispSample = " 20Sec";
          break;            
        case TASK_60SEC :DispSample = " 60Sec";
          break;     
      }  
      display.print("    ");      //4 
      display.print(DispSample); 
}

void displayValues(void)
{
  if(DisplayInitDelay == OFF)return;

  //testdrawchar();
  //return;
  
  display.clearDisplay();
  display.setTextSize(1);
     display.setCursor(0, 1);
/*  
   display.setCursor(0, 1);
    display.print(Str_Time); 
    display.print(' ');    
    display.println(Str_Date);   
*/
      display.print(Str_Date);   //10
      display.print("   ");
      display.println(Str_Time);     //8
            


    
    if(SDCard.Status != SD_NOT_Present){
    //   if (SDCard.LogStatus)SDCard_or_File(); 
    //   else SDcard_Info();
       SDCard_or_File();           
    }
    else //display.print("Can't Read!");//11
           display.print("SD problem!");//11

/*
      switch(SDCard.Status){

        case 1 :display.print("SD1 ");display.print(SD_Volume);display.print("Gb ");//ShowLogTime(); //4+5+3+9 = 21
        break;
        case 2 :display.print("SD2 ");display.print(SD_Volume);display.print("Gb ");//ShowLogTime(); //74+5+3+9 = 21
        break;
        case 3 :display.print("SDH ");display.print(SD_Volume);display.print("Gb ");//ShowLogTime();//4+5+3+9 = 21
        break; 
         case 0 ://display.print("No Card  Reset 2 Run ");// 21  SD_NOT_Present
                  //display.print("Can't Read!     Reset");// 21
        //break;
        default://display.print("Unknown Problem !");   
                 // display.print("Can't Read!     Reset");// 21 
                  display.print("Can't Read! ");// 21   
         break;
     } 
*/
      
    ShowLogTime();
    display.println();
    unsigned long Remain;
     unsigned long   Remain2;
   display.print(' ');
    if( FileSize.Total) {
      if(FileSize.Total < 100000000)display.print(' ');   // 100 Mb     
      if(FileSize.Total < 10000000)display.print(' ');   // 10 Mb
      
      if(FileSize.Total < 1000000)display.print(' ');   // 1 Mb
      if(FileSize.Total < 100000)display.print(' ');   // 100 kb
      if(FileSize.Total < 10000)display.print(' ');   // 10 kb
      
      if(FileSize.Total < 1000)display.print(' ');   // 1 kb
      if(FileSize.Total < 100)display.print(' ');   // 100 byte
      if(FileSize.Total < 10)display.print(' ');   // 10  byte  


   if(FileSize.Total >= 1000000){     
      display.print(FileSize.Total / 1000000);  // 9 digit 
      display.print('.');  // 9 digit 
      Remain = FileSize.Total % 1000000;        
      if(Remain < 100000)display.print('0'); //  _50000
      if(Remain < 10000)display.print('0');  //  __5000
      if(Remain < 1000)display.print('0');  //  ___500
      
      
     // display.print('.');  // 9 digit
    if(Remain  >= 1000){
      Remain2 = Remain % 1000;
       display.print(Remain / 1000);  // 9 digit 
       display.print('.');  // 9 digit
      if(Remain2 < 100)display.print('0');
      if(Remain2 < 10)display.print('0');
      display.print(Remain2);  // 9 digit       
    }

      
    }
    else if(FileSize.Total >= 1000){
       Remain = FileSize.Total % 1000;
      display.print(FileSize.Total / 1000);  // 9 digit 
      display.print('.');  // 9 digit 
      if(Remain < 100)display.print('0');
      if(Remain < 10)display.print('0');
      display.print(Remain);  // 9 digit 
    }
    else display.print(FileSize.Total); // less than 1000


      
               
  //    display.print(FileSize.Total);  // 9 digit 
      display.print(" Bytes"); //6 digit  total 15
    }
    else display.print("                    ");


     
   /*
    if(SDCard.Status != SD_NOT_Present){
      if (SDCard.LogStatus){
       // display.print("File ");
        display.print(LOG_FILE_SHORT);  //6  21-6 = 15 14 //      123456789 Byte
        display.print(FileSize);
        display.print(" Byte");
      }
      else //display.print("LOG OFF Sample:");//15
          display.print("      Log. Off       ");//21        
    }
    else  display.print("                     ");//21
    */

    display.println();
     //4th line
   // DisplayFullSensors();
    DisplayTestDevices();
  
    display.setCursor(0, 57);
    DisplayMenu();

   display.display();
}

//String Disp_MENU_NULL = "ENTER  UP DOWN    ESC";
String Disp_MENU_NULL_ENT = "ENTER     ";
String Disp_MENU_NULL_ESC = "     ESC";

String Disp_MENU1 =     "LOG START & STOP MENU";
String Disp_MENU2 =     "LOG SAMPLE TIME MENU ";
String Disp_MENU3 =     "DISPLAY STANDBYE MENU";

String Disp_MENU1_SUB1= "START LOG? If Yes ENT"; 
String Disp_MENU1_SUB2= "STOP LOG? If Yes ENT ";  
String Disp_MENU3_SUB1= "STNDBY Enb?If Yes ENT"; 
String Disp_MENU3_SUB2= "STNDBY Dis?If Yes ENT";  

String Disp_MENU2_SUB= "Enter -> ";  //9
String Disp_MENU2_SUB1= " 500 mSec   "; //12
String Disp_MENU2_SUB2= " 1 Sec      "; //12
String Disp_MENU2_SUB3= " 2 Sec      "; //12
String Disp_MENU2_SUB4= " 5 Sec      "; //12
String Disp_MENU2_SUB5= " 10 Sec     "; //12
String Disp_MENU2_SUB6= " 20 Sec     "; //12
String Disp_MENU2_SUB7= " 60 Sec     "; //12

void DisplayMenu(void){
  switch(Menu){
    case MENU_NULL :// display.print(Disp_MENU_NULL); 
          display.print(Disp_MENU_NULL_ENT);                           
          display.write(30);  
          display.write(' '); 
          display.write(31); 
          display.print(Disp_MENU_NULL_ESC);                    
      break;
    case MENU1 :     display.print(Disp_MENU1); 
      break;
    case MENU2 :     display.print(Disp_MENU2); 
      break;
    case MENU3 :     display.print(Disp_MENU3); 
      break;

    case MENU1_SUB1 :display.print(Disp_MENU1_SUB1); 
      break;
    case MENU1_SUB2 :display.print(Disp_MENU1_SUB2); 
      break;

    case MENU2_SUB1 : display.print(Disp_MENU2_SUB); display.print(Disp_MENU2_SUB1);  
      break;
    case MENU2_SUB2 : display.print(Disp_MENU2_SUB); display.print(Disp_MENU2_SUB2);    
      break;
    case MENU2_SUB3 : display.print(Disp_MENU2_SUB); display.print(Disp_MENU2_SUB3);   
      break;
    case MENU2_SUB4 :display.print(Disp_MENU2_SUB); display.print(Disp_MENU2_SUB4);    
      break;
    case MENU2_SUB5 :display.print(Disp_MENU2_SUB); display.print(Disp_MENU2_SUB5);    
      break;
    case MENU2_SUB6 : display.print(Disp_MENU2_SUB); display.print(Disp_MENU2_SUB6);   
      break;
    case MENU2_SUB7 :display.print(Disp_MENU2_SUB); display.print(Disp_MENU2_SUB7);    
      break;

    case MENU3_SUB1 : display.print(Disp_MENU3_SUB1);  
      break;
    case MENU3_SUB2 :  display.print(Disp_MENU3_SUB2); 
      break;

    default: 
    break;
  }
}
void DisplayFullSensors(void){
    display.print("x");
    display.print(Accelometer.x); //6
    
    display.print(" y");
    display.print(Accelometer.y); //7
    

     display.print(" z");
     display.println(Accelometer.z); //7     
    
    
    display.print(Values.TemperatureSi072_Ch1,1);
   //  display.print("°");                     
    display.print("C %");
    display.print(Values.Humidity_Ch1,1); //
    display.print(" Lm:");
    display.println(Values.Luminosity); //

    display.print(Values.Pressure,0);
    display.print("hPA ");
    display.print(Values.TemperatureBMP,1);
   //  display.print("\0x7F");   
    display.print("C ");  
    display.print(Values.Altitude,1);
    display.println("m"); 
}

void DisplayTestDevices(void){
   //  display.print("");
/*
     display.print(Current_Mains_Raw); //7     

     display.print(" ");
     display.print(Mains_Volt_Raw); //7  
*/
     display.print(" ");
     display.print(Mains_Volt); //7 
     display.print("V ");

     display.print(Current_Mains_Rms); //7  
     display.println("A");

   //  display.println(" Ia");

     
  // display.print("1:"); 
    if (!isnan(Values.TemperatureSi072_Ch1)) {
          display.print(Values.TemperatureSi072_Ch1,1);                    
          display.write(247);display.print("C"); 
    }
    else  display.print("------");  


   
   if (!isnan(Values.Humidity_Ch1)) {
    display.print(" %");
    display.print((int)Values.Humidity_Ch1); // 
   }
    else  display.print("----");  
      
    display.print(" ");


  // display.print("2:");  
   if (!isnan(Values.TemperatureSi072_Ch2)) {
        display.print(Values.TemperatureSi072_Ch2,1);
        display.write(247);display.print("C"); 
   }
    else  display.print("------");  

    if (!isnan(Values.Humidity_Ch2)) {
    display.print(" %");
    display.print((int)Values.Humidity_Ch2); // 
   }
    else  display.print("----");      

  //  display.print(" ");
 //  display.print("3:");  
      display.println(""); 
     if (!isnan(Values.TemperatureSi072_Ch3)) {
        display.print(Values.TemperatureSi072_Ch3,1);
        display.write(247);display.print("C"); 
   }
    else  display.print("------");  

    if (!isnan(Values.Humidity_Ch3)) {
    display.print(" %");
    display.print((int)Values.Humidity_Ch3); // 
   }
    else  display.print("----");     

    display.print(" "); // 
    display.print("PM2.5 ");
    if(Values.PM25 < 100.00)display.println(Values.PM25,1);
    else display.println(Values.PM25,0);
      
    
    //

    
    
  //  display.println(deBugString); // 

    switch(DisplayValueTimer){
      case 0:     
          display.print("Dev Id:  "); // 
          display.print(EE_Id_EString); //
         break;
         case 1:
          display.print("1.   "); // SI072_FIRST_SENSOR
          display.println(Sensor1_Id);
         break;
         case 2:
          display.print("2.   "); // SI072_SECOND_SENSOR
          display.println(Sensor2_Id);
         break;
         case 3:        
            display.print("3.   "); // SI072_THIRD_SENSOR
            display.println(Sensor3_Id);
         break;
         default:
         break;  
    }      
}
