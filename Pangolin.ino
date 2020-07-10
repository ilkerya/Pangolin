/*
 Rev   Date         Description
 1.0   12.02.2020   Initial release
*/
 //for setting date&time open arduino serial monitor and send the data stream
 //   Year,Month,Date,Hour,Minute;Second
 //   2020,05,27,21,14,23
 //  2020,07,07,19,00,50
 // EEEEf567 
 // 115200 baud Both NL & CR
 // put leading zero for numbers less than 10

 //*********************************************************************
 
 // #define DEBUG_SIMULATOR_MODE // For DEbugging As A Simulator
 

 #define ARDUINO_MEGA // 8 bit AVR
 //#define ARDUINO_DUE // ARM Cortex M3

#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
#include <avr/wdt.h>

#define CS_PIN 8              //8-->Arduino Zero. 15-->ESP8266 
/*
///  ADE9153A INIT
#define ARM_MATH_CM0PLUS
#include  <ADE9153A.h>
#include <ADE9153AAPI.h>
// Basic initializations 
#define SPI_SPEED 1000000     //SPI Speed
#define CS_PIN 8              //8-->Arduino Zero. 15-->ESP8266 
#define ADE9153A_RESET_PIN 4  //On-board Reset Pin
#define USER_INPUT 5          //On-board User Input Button Pin
#define LED 6                 //On-board LED pin
ADE9153AClass ade9153A;

struct EnergyRegs energyVals;  //Energy register values are read and stored in EnergyRegs structure
struct PowerRegs powerVals;    //Metrology data can be accessed from these structures
struct RMSRegs rmsVals;  
struct PQRegs pqVals;
struct AcalRegs acalVals;
struct Temperature tempVal;

void readandwrite(void);
void resetADE9153A(void);

int ledState = LOW;
int inputState = LOW;
unsigned long lastReport = 0;
const long reportInterval = 2000;
const long blinkInterval = 500;
*/
///  ADE9153A END
    
#include "RTClib.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Adafruit_Si7021.h"
#include "Adafruit_TSL2591.h"
#include "Adafruit_BMP3XX.h"
#include "Arduino_LSM9DS1.h"
#include <SdsDustSensor.h> // https://github.com/lewapek/sds-dust-sensors-arduino-library


// C:\Users\Yagciilk\Documents\Arduino\Pangolin

#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_Def.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_Variables.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_RTC.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_SDCard.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_Display.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_Sensors.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_Functions.h"

#ifdef ARDUINO_DUE
void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk((uint32_t)irq);
  TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  //    uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
  uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
  TC_SetRA(tc, channel, rc/2); //50% high, 50% low
  TC_SetRC(tc, channel, rc);
  TC_Start(tc, channel);
  tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
  tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
  NVIC_EnableIRQ(irq);
}
#endif


void setup() {
   byte RESET_CASE = MCUSR;

      pinMode(53, OUTPUT);  // SS Pin high to avoid miscommunication
   digitalWrite(53, HIGH);  
  
     pinMode(10, OUTPUT);
   digitalWrite(10, HIGH);  

     pinMode(4, OUTPUT);  // ADE9153A_RESET_PIN
   digitalWrite(4, HIGH);  
/*
    pinMode(A0, OUTPUT);
    digitalWrite(A0, HIGH);

    pinMode(A2, OUTPUT);
    digitalWrite(A2, LOW);
*/
 //   pinMode(A5, INPUT);
 //   digitalWrite(A5, LOW);
    
  //  pinMode(A5, OUTPUT);
 //   digitalWrite(A5, LOW);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  delay(10);


        Serial.print("MCUSR: ");
        Serial.println(RESET_CASE);


  if(MCUSR & WDRF) {
    Serial.print("Rebooting from a Watchdog Reset");
  }
  else if(MCUSR & BORF) {
    Serial.print("Rebooting from a Brown-out Reset");
  }
  else if(MCUSR & EXTRF) {
    Serial.print("Rebooting from an External Reset");
  }
   else if(MCUSR & PORF) {
              Serial.print("Rebooting from a Power On Reset");
  }

        if(MCUSR & (1<<WDRF)){
            // a watchdog reset occurred
            Serial.print("Rebooting from a Watchdog Reset");
          } 
          if(MCUSR & (1<<BORF)){
            Serial.print("Rebooting from a Brown-out Reset");
          }
          //  a brownout reset occurred       
         if(MCUSR & (1<<EXTRF)){
            //  an external reset occurred
            Serial.print("Rebooting from an External Reset");
         }       
          if(MCUSR & (1<<PORF)){
              //  a power on reset occurred
              Serial.print("Rebooting from a Power On Reset");
          }

          //Clear register
           MCUSR = 0x00;

  //  SDCard.LogStatus = 0;      // default start with log off;
  EEReadLog();
  SDCard.LogStatusInit = 0;  // put the header of the csv file 

   Serial.print("SDCard.LogStatus: ");  
   Serial.print(SDCard.LogStatus); 
   Serial.print("    SampleTime: ");  
   Serial.println(SampleTime); 
       
  
    pinMode(LED_GREEN, OUTPUT);           // set pin to input
    digitalWrite(LED_GREEN, LOW);       // turn on pullup resistors  
    pinMode(LED_RED, OUTPUT);           // set pin to input
    digitalWrite(LED_RED, LOW);       // turn on pullup resistors


    pinMode(KEY_LEFT, INPUT);           // set pin to input
    pinMode(KEY_LEFT,INPUT_PULLUP);

    pinMode(KEY_MID, INPUT);           // set pin to input
    pinMode(KEY_MID,INPUT_PULLUP);

    pinMode(KEY_RIGHT, INPUT);           // set pin to input
    pinMode(KEY_RIGHT,INPUT_PULLUP);
    //wdt_enable(WDT0_1S);

    wdt_reset();
    wdt_enable(WDTO_8S);
    //https://www.nongnu.org/avr-libc/user-manual/group__avr__watchdog.html
   
    
    #ifdef ARDUINO_MEGA
       ADCSRA &= ~ (1 << ADEN);            // turn off ADC to save power ,, enable when needed and turn off again
    #endif


    ShowSerialCode();
        
 /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  */
 #ifndef DEBUG_SIMULATOR_MODE
    Sensors_PeripInit();
  #endif


    #ifdef ARDUINO_MEGA
     #endif

    #ifdef ARDUINO_MEGA
             // initialize timer1 
      noInterrupts();           // disable all interrupts
      TCCR1A = 0;
      TCCR1B = 0;
   //    TCNT1 = 34286;            // preload timer 65536-16MHz/256/2Hz 500mS
       TCNT1 = 64286;            // preload timer 65536-16MHz/256/50Hz 20 ms       
       TCCR1B |= (1 << CS12);    // 256 prescaler 
       TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
       interrupts(); 
     #endif
     
     #ifdef ARDUINO_DUE
     startTimer(TC1, 0, TC3_IRQn, 64); //TC1 channel 0, the IRQ for that channel and the desired frequency
     #endif
}
#ifdef ARDUINO_DUE
void TC3_Handler(){
        TC_GetStatus(TC1, 0);
        digitalWrite(LED_GREEN, digitalRead(LED_GREEN) ^ 1);  
        //digitalWrite(13, l = !l);
}
#endif

// interrupt vector

    #ifdef ARDUINO_MEGA
ISR(TIMER1_OVF_vect){        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
 //   TCNT1 = 34286;            // preload timer for 500mSec
       TCNT1 = 64286;            // preload timer for 20mSec
    #endif
    #ifdef ARDUINO_DUE
void TC3_Handler(){
        TC_GetStatus(TC1, 0);
    #endif
       
    IntTimer250++;
    IntTimer500 ++;
    IntTimer1 ++;
    IntTimer2 ++;
    IntTimer5 ++;
    IntTimer10 ++;
    IntTimer20 ++;   
    IntTimer60 ++;   

    if(IntTimer250 >= 13){
      IntTimer250 = 0;
      LoopTask_250msec = ON;
    }
    if(IntTimer500 >= 25){ // 500 msec
      IntTimer500 = 0;
      LoopTask_500msec = ON;
    }
    if(IntTimer1 >= 50){  // 1 sec
      IntTimer1 = 0;
      LoopTask_1Sec = ON;
      digitalWrite(LED_GREEN, digitalRead(LED_GREEN) ^ 1);  
   
      if(DisplaySleepEnable == ON){
        if(OLED_Timer) OLED_Timer--;   // sleep active
      }
      else OLED_Timer = 32768; // no sleep    
      if(DisplayInitDelay == OFF)DisplayInitDelay = ON;           
    }
    if(IntTimer2 >= 100){ // 2 sec
      IntTimer2 = 0;
      LoopTask_2Sec = ON;
    }
    if(IntTimer5 >= 250){  // 5 sec
      IntTimer5 = 0;
      LoopTask_5Sec = ON;
    }
    if(IntTimer10 >= 500){  // 10 sec
      IntTimer10 = 0;
      LoopTask_10Sec = ON;
    }
    if(IntTimer20 >= 1000){  // 20 sec
      IntTimer20 = 0;
      LoopTask_20Sec = ON;
    }
    if(IntTimer60 >= 3000){  // 60 sec
      IntTimer60 = 0;
      LoopTask_60Sec = ON;
    }        
    Key_Functions();
       //  digitalWrite(LED_RED, digitalRead(LED_RED) ^ 1);
     //   if(!digitalRead(KEY_LEFT) || !digitalRead(KEY_MID) || !digitalRead(KEY_RIGHT))
}
// the loop function runs over and over again forever
void loop() {
    MainLoop(); 
     wdt_reset();
}       
