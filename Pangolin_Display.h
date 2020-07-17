
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
/*
void SDcard_Info(){
       if(SDCard.Status = SD1_TYPE)Display_Line2 = "SD1 ";         
       else if(SDCard.Status = SD2_TYPE)Display_Line2 = "SD2 ";           
       else if(SDCard.Status = SDHC_TYPE)Display_Line2 = "SDH ";
       Display_Line2 += String(SD_Volume) + "Gb" ;            
}
*/
void SDCard_or_File(){
    switch(DisplayValueTimer){
      case 0:
      case 2:     
           if(SDCard.Status = SD1_TYPE)      Display_Line2 = "SD1 ";         
           else if(SDCard.Status = SD2_TYPE) Display_Line2 = "SD2 ";           
           else if(SDCard.Status = SDHC_TYPE)Display_Line2 = "SDH ";
           Display_Line2 += String(SD_Volume) + "Gb" ; 
      break;
         case 1:
         case 3: 
           Display_Line2 = String(LOG_FILE) + ' ';
         break;
         default:
         break;  
    }      
}

void UpdateSD_LogTime(){
    if(SDCard.Status != SD_NOT_Present)SDCard_or_File();           
    else Display_Line2 = "SD problem!";
    Display_Line2 += "    ";
    //  String DispSample="";
      switch(SampleTime){
       case TASK_500MSEC:Display_Line2 += "0.5Sec"; //5 
          break;        
        case TASK_1SEC : Display_Line2 += "  1Sec";//5
          break; 
        case TASK_2SEC : Display_Line2 += "  2Sec";
          break;        
        case TASK_5SEC : Display_Line2 += "  5Sec";
          break;  
        case TASK_10SEC :Display_Line2 += " 10Sec";
          break; 
        case TASK_20SEC :Display_Line2 += " 20Sec";
          break;            
        case TASK_60SEC :Display_Line2 += " 60Sec";
          break;     
      }  
}

void UpdateFileSize(){
    String str;
     unsigned long Remain;
     unsigned long   Remain2;
    str = ' ';
    if( FileSize.Total == 0) str += "                    ";//20 
    
      if(FileSize.Total < 100000000)str += ' ';   // 100 Mb     
      if(FileSize.Total < 10000000)str += ' ';   // 10 Mb
      
      if(FileSize.Total < 1000000)str += ' ';   // 1 Mb
      if(FileSize.Total < 100000)str += ' ';   // 100 kb
      if(FileSize.Total < 10000)str += ' ';   // 10 kb
      
      if(FileSize.Total < 1000)str += ' ';   // 1 kb
      if(FileSize.Total < 100)str += ' ';   // 100 byte
      if(FileSize.Total < 10)str += ' ';   // 10  byte  

      if(FileSize.Total >= 1000000){     
        str += String(FileSize.Total / 1000000);  // 9 digit 
        str +='.';  // 9 digit 
        Remain = FileSize.Total % 1000000;        
        if(Remain < 100000)str += ' '; //  _50000
        if(Remain < 10000)str += ' ';  //  __5000
        if(Remain < 1000)str += ' ';  //  ___500
      
        if(Remain  >= 1000){
          Remain2 = Remain % 1000;
          str += String(Remain / 1000);  // 9 digit 
          str +='.';   // 9 digit
          if(Remain2 < 100)str += '0';
          if(Remain2 < 10)str += '0';
          str += String(Remain2);  // 9 digit       
        }  
      }
      else if(FileSize.Total >= 1000){
        Remain = FileSize.Total % 1000;
        str += String(FileSize.Total / 1000);  // 9 digit 
        str +='.';   // 9 digit 
        if(Remain < 100)str += '0';
        if(Remain < 10)str += '0';
        str += String(Remain);  // 9 digit 
      }
      else str += String(FileSize.Total); // less than 1000 
             
      str += String(" Bytes   "); //9 digit  total 15   
      Display_Line3 = str;
}

void PrintDisplayBuffer(void){
      Serial.println();
      Serial.println();
      Serial.println("   DISPLAY  8x21     ");
      Serial.println(Display_Line1);
      Serial.println(Display_Line2);
      Serial.println(Display_Line3);
      Serial.println(Display_Line4);
      Serial.println(Display_Line5);
      Serial.println(Display_Line6);
      Serial.println(Display_Line7);
      Serial.println(Display_Line8);
      Serial.println();
      Serial.println();   

    // Additionals
    Serial.print("DevId: ");Serial.print(EE_Id_EString);
    Serial.print("    Sensor1: ");Serial.print(Sensor1_Id);
    Serial.print("    Sensor2: ");Serial.print(Sensor2_Id);
    Serial.print("    Sensor3: ");Serial.print(Sensor3_Id);

    Serial.println();   
    Serial.println( "Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__); 

    Serial.println();
    Serial.println();
        
}

void UpdateDisplayBuffer(void){
    String *str;
    Display_Line1 = String(Str_Date) + "   " + String(Str_Time);
    
   // ShowLogTime();
    UpdateSD_LogTime();// Line2
    UpdateFileSize();// Line3
    UpdateSensorsTHVA();// Line4 Line 5
    // DisplayFullSensors();
    DisplayMenu(); // Line8
    
}

void displayValues(void)
{
  UpdateDisplayBuffer();
  if(DisplayInitDelay == OFF)return;

  //testdrawchar();
  //return;

    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.print(Display_Line1);   //10

    display.setCursor(0, 8);
    display.print(Display_Line2);   //10
  
    display.setCursor(0, 16);
    display.print(Display_Line3);   //10 

    display.setCursor(0, 24);
    display.print(Display_Line4);   //10 

    display.setCursor(0, 32);
    display.print(Display_Line5);   //10 

    if(DispExpSens1){
      DispExpSens1 = OFF;
      display.setCursor(24, 32); //x,y  6*4 = 24
      display.write(247); // 5th character  '°';   
    }
    if(DispExpSens2){
      DispExpSens2 = OFF;
      display.setCursor(90, 32); //x,y  6*15 = 90
      display.write(247); // 5th character  '°';    
    }
     
    display.setCursor(0, 40);
    display.print(Display_Line6);   //10 

    if(DispExpSens3){
      DispExpSens3 = OFF;
      display.setCursor(24, 40); //x,y
      display.write(247); // 5th character  '°';    
    }
    display.setCursor(0, 48);
    display.print(Display_Line7);   //10 
 
    display.setCursor(0, 56); // 8th line
    display.print(Display_Line8);   //10 

    if( DispExpLin8_1){
      DispExpLin8_1 = OFF;
      display.setCursor(60, 56); //x,y  6*4 = 24
      display.write(30); // 5th character  '°';  

      display.setCursor(72, 56); //x,y  6*4 = 24
      display.write(31); // 5th character  '°';        
    }

   display.display();
}

//String Disp_MENU_NULL = "ENTER  UP DOWN    ESC";
String Disp_MENU_NULL_ENT = "ENTER     "; // 10
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
    case MENU_NULL : Display_Line8 = Disp_MENU_NULL_ENT;Display_Line8 += "   ";Display_Line8 += Disp_MENU_NULL_ESC;
    DispExpLin8_1 = ON; // exception to show up down characters                    
      break;
    case MENU1 :  
    Display_Line8 = Disp_MENU1;
      break;
    case MENU2 :   
    Display_Line8 = Disp_MENU2;
      break;
    case MENU3 :   
    Display_Line8 = Disp_MENU3;
      break;
    case MENU1_SUB1 :Display_Line8 = Disp_MENU1_SUB1;
      break;
    case MENU1_SUB2 : Display_Line8 = Disp_MENU1_SUB2;
      break;
    case MENU2_SUB1 : Display_Line8 = Disp_MENU2_SUB;Display_Line8 += Disp_MENU2_SUB1;   
      break;
    case MENU2_SUB2 : Display_Line8 = Disp_MENU2_SUB; Display_Line8 += Disp_MENU2_SUB2;  
      break;
    case MENU2_SUB3 : Display_Line8 = Disp_MENU2_SUB; Display_Line8 += Disp_MENU2_SUB3;
      break;
    case MENU2_SUB4 : Display_Line8 = Disp_MENU2_SUB; Display_Line8 += Disp_MENU2_SUB4;
      break;
    case MENU2_SUB5 : Display_Line8 = Disp_MENU2_SUB; Display_Line8 += Disp_MENU2_SUB5;   
      break;
    case MENU2_SUB6 : Display_Line8 = Disp_MENU2_SUB; Display_Line8 += Disp_MENU2_SUB6;
      break;
    case MENU2_SUB7 : Display_Line8 = Disp_MENU2_SUB; Display_Line8 += Disp_MENU2_SUB7; 
      break;
    case MENU3_SUB1 : Display_Line8 = Disp_MENU3_SUB1;
      break;
    case MENU3_SUB2 :  Display_Line8 = Disp_MENU3_SUB2;
      break;
    default: 
    break;
  }
}

void UpdateSensorsTHVA(void){

    String str;
    str += " " + String(Mains_Volt) + "V ";
    str += String(Current_Mains_Rms) + "A ";   
    Display_Line4 = str;
  
    str = "";
    if (!isnan(Values.TemperatureSi072_Ch1)) {
          str += String(Values.TemperatureSi072_Ch1,1);
          str += " C";  DispExpSens1 = ON;
         //  str += '°';                          
    }
    else  str += "------";  
       
   if (!isnan(Values.Humidity_Ch1)) {
    str +=" %";
    str += String((int)Values.Humidity_Ch1); // 
   }
    else   str +="----";  
    str +=" ";

    if (!isnan(Values.TemperatureSi072_Ch2)) {
          str += String(Values.TemperatureSi072_Ch2,1);
           str += " C";   DispExpSens2 = ON;                   
        //  str += '°'; 
    }
    else  str += "------";  
       
   if (!isnan(Values.Humidity_Ch2)) {
    str +=" %";
    str += String((int)Values.Humidity_Ch2); // 
   }
    else   str +="----";  

    
    Display_Line5 = str;

    str = "";
    if (!isnan(Values.TemperatureSi072_Ch3)) {
          str += String(Values.TemperatureSi072_Ch3,1);
          str += " C";    DispExpSens3 = ON;
     // str += '\°'; 
         // str += '/247';   olmaz             
          //display.write(247);
      //    str +="C"; 
    }
    else  str += "------";  
       
   if (!isnan(Values.Humidity_Ch3)) {
    str +=" %";
    str += String((int)Values.Humidity_Ch3); // 
   }
    else   str +="----";  
    

    str += " "; // 
    str += "PM2.5 ";
    if(Values.PM25 < 100.00)str +=  String(Values.PM25,1);
    else str += String(Values.PM25,0);

    Display_Line6 = str;

    str = "";
    switch(DisplayValueTimer){
      case 0:     
          str += "Dev Id:  " + EE_Id_EString;
         break;
         case 1:
          str += "1.   " + Sensor1_Id;
         break;
         case 2:
          str += "2.   " + Sensor2_Id;
         break;
         case 3:        
            str += "3.   " + Sensor3_Id;
         break;
         default:
         break;  
    }  

     Display_Line7 = str;
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
