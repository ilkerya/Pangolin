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
// C:\Projects\Pangolin\..   Atmel Studio Project Path
// C:\Projects\Pangolin\Pangolin\ArduinoCore\include\libraries\...  Atmel Studio Toolchain Compiler Lib Paths    
#include "RTClib.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Adafruit_Si7021.h"
#include "Adafruit_TSL2591.h"
#include "Adafruit_BMP3XX.h"
#include "Arduino_LSM9DS1.h"
#include "SdsDustSensor.h" // https://github.com/lewapek/sds-dust-sensors-arduino-library


// C:\Users\Yagciilk\Documents\Arduino\Pangolin

#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_Def.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_Variables.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_RTC.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_SDCard.h"
#include  "C:\Users\Yagciilk\Documents\Arduino\Pangolin\Pangolin_UI.h"
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
  MicroInit();
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
      PrintDisplayBuffer();
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
    Common_Loop(); 
     wdt_reset();
}       
