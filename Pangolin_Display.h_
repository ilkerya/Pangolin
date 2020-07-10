
//https://github.com/adafruit/Adafruit_SSD1306


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
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
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
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
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

void displayValues(void)
{
  if(DisplayInitDelay == OFF)return;
  
  display.clearDisplay();
  display.setTextSize(1);
        display.setCursor(0, 1);
    //display.print("->");

    display.print(Str_Time); 
    display.print(' ');    
    display.println(Str_Date);       
    //Str_Date + Str_Time + ' ';  
/*
      DateTime now = rtc.now();

       //       display.setCursor(0, 1);
       //       display.setCursor(1, 1);
    if(now.hour()<10)display.print(' ');           
    display.print(now.hour(), DEC);
    display.print(':');
    if(now.minute()<10)display.print('0');      
    display.print(now.minute(), DEC);
    display.print(':');
    if(now.second()<10)display.print('0');        
    display.print(now.second(), DEC);
    display.print(" ");

   display.print(daysOfTheWeek[now.dayOfTheWeek()]);

   // display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  
     display.print(" ");   
  //  display.print(now.year(), DEC);
 //   display.print('/');
    if(now.month()<10)display.print('0');   
    display.print(now.month(), DEC);
    display.print('/');
    if(now.day()<10)display.print('0');   
    display.println(now.day(), DEC);
*/
   // display.print("Card:");//5

  
      switch(SDCard.Status){
        case 0 :display.print("No Card  Reset 2 Run");// 26
        break;
        case 1 :display.print("SD1 Card ");display.print(SD_Volume);display.print(" Gb ");
        break;
        case 2 :display.print("SD2 Card ");display.print(SD_Volume);display.print(" Gb ");
        break;
        case 3 :display.print("SDHC Card ");display.print(SD_Volume);display.print(" Gb");
        break; 
        default://display.print("Unknown Problem !");   
                  display.print("Card Problem    !");       
     }
     display.println();
    
    
    if(SDCard.Status != SD_NOT_Present){
      if (SDCard.LogStatus){
        display.print("Log2 ");
        display.print(LOG_FILE);  // 8 left
      }
      else display.print("LOG OFF Sample:");//15
      String DispSample="";
      switch(SampleTime){
       case TASK_500MSEC:DispSample = " 500mS";
          break;        
        case TASK_1SEC : DispSample = "  1Sec";
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
      display.println(DispSample);       
    }
    else{
      Serial.println("Card Problem");
        display.println("Problem");    
    }
     //4th line
  /*  
    //display.print("WindRaw:");
    display.print(RV_ADunits);
    display.print('/');    
    //display.print("WindTemp:");
    display.print(Values.WindTemp);
     display.print('/');    
  //  display.print("WindMPH:");
    display.println(Values.WindMPH);
*/
    display.print("x");
    display.print(Accelometer.x); //6
    
    display.print(" y");
    display.print(Accelometer.y); //7
    

     display.print(" z");
     display.println(Accelometer.z); //7     
    
    
    display.print(Values.TemperatureSi072,1);
   //  display.print("°");                     
    display.print("C %");
    display.print(Values.Humidity,1); //
    display.print(" Lm:");
    display.println(Values.Luminosity); //

    display.print(Values.Pressure,0);
    display.print("hPA ");
    display.print(Values.TemperatureBMP,1);
   //  display.print("\0x7F");   
    display.print("C ");  
    display.print(Values.Altitude,1);
    display.println("m");  
   /*  
    display.print("Menu:");
    display.print(Menu);    
    display.print(" OLEDTmr:");
    display.println(OLED_Timer); 
 */        
    display.setCursor(0, 57);
    DisplayMenu();
    
 /*   
    display.print("Str:");
    display.print(IndxStr);
    display.print("End:");
    display.print(IndxEnd);
    display.print("Ctr:");
    display.println(IndxCount);

    display.print("OLED_Timer: ");
    display.println(OLED_Timer);

                    
    display.print("KeyLogger:");
    display.println(KeyLogger);


    for (int i = 0; i < IndxStr ; i++){
        display.print(' ');
    }   
    for (int i = IndxCount;  i < IndxEnd- IndxStr + IndxCount ; i++){
        display.print(DisplayLine[i]);   
    }
    if(IndxStr)IndxStr--;//
    else IndxCount++;  

      if(IndxCount>=20){
        IndxEnd--;
      }
      if(IndxCount>=25){
        IndxCount =0; // all default
        IndxStr = DEF_START_NULL_LINES;
        IndxEnd = DEF_END_LINE_INDEX;
      }
*/

       
  /*            
    display.print("Left:");
    display.print(digitalRead(KEY_LEFT));

    display.print("Mid:");
    display.print(digitalRead(KEY_MID));
    
     display.print("Right:");
    display.println(digitalRead(KEY_RIGHT));   
     display.print(KeyLeft_Rel);
     display.print(KeyMid_Rel);
     display.print(KeyRight_Rel);

  */  
    //   display.print("SDCardStatus: ");
    // display.println(SDCardStatus);  
   // display.print("RTC_Test: ");
  //  display.println(RTC_Test);
    
    
   display.display();
}

String Disp_MENU_NULL = "ENTER  UP DOWN    ESC";
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
    case MENU_NULL : display.print(Disp_MENU_NULL); 
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
