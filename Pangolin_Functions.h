
// https://www.onlinegdb.com/edit/Hkmlxi_08




void Common_Loop(){
  
  if (LoopTask_250msec) {
    LoopTask_250msec = OFF;

    // One time after wake up form sleep
    if (OLED_Init == ON) {
#ifndef DEBUG_SIMULATOR_MODE
      Display_ReInit(20);
#endif
      OLED_Init = OFF;
    }
    if (OLED_Timer) {
#ifndef DEBUG_SIMULATOR_MODE
      displayValues();
#endif
    }
    else {
#ifndef DEBUG_SIMULATOR_MODE
      Display_SwitchOff();
#endif
    }
#ifdef LEM_CURRENT_EXISTS
    AnalogValRead();
#endif

  }
  if (LoopTask_500msec) {
    LoopTask_500msec = OFF;
    if (SampleTime == TASK_500MSEC) SD_CardLogTask();
  }

  if (LoopTask_1Sec) {
    LoopTask_1Sec = OFF;
#ifndef DEBUG_SIMULATOR_MODE

    SerialPortRx();
    RTC_TimeClock();

#ifdef WIND_SENSOR_EXISTS
    WindSensorRead();
#endif

#ifdef TEMP_HUM_1_SENSOR_EXISTS
    deBugString = "TmpHmSn1_1";
    SensorRead_Si072(SI072_FIRST_SENSOR); // MULTIPLEXER NO
    deBugString = "TmpHmSn1_2";
#endif
#ifdef TEMP_HUM_2_SENSOR_EXISTS
    deBugString = "TmpHmSn2_1";
    SensorRead_Si072(SI072_SECOND_SENSOR); // MULTIPLEXER NO
    deBugString = "TmpHmSn2_2";
#endif
#ifdef TEMP_HUM_3_SENSOR_EXISTS
    deBugString = "TmpHmSn3_1";
    SensorRead_Si072(SI072_THIRD_SENSOR); // MULTIPLEXER NO
    deBugString = "TmpHmSn3_2";
#endif



#ifdef  BAR_PRES_SENSOR_EXISTS
    SensorAlt_Read();
#endif
#ifdef LIGHT_SENSOR_EXISTS
    SensorLight_Read();
#endif
#ifdef ACCL_GYRO_SENSOR_EXISTS
    SensorAcccel_GyroRead();
#endif
#endif // end of  #ifndef DEBUG_SIMULATOR_MODE

    KeyTimeOutCheck();

    if (SampleTime == TASK_1SEC) SD_CardLogTask();


  }
  
  if (LoopTask_2Sec) {
    LoopTask_2Sec = OFF;
    if (SampleTime == TASK_2SEC) SD_CardLogTask();

      UpdateDispRoll();

  }
  if (LoopTask_5Sec) {
    LoopTask_5Sec = OFF;
    if (SampleTime == TASK_5SEC) SD_CardLogTask();

    SDS_DustSensor();

    DisplayValueTimer++;
    if (DisplayValueTimer > 4)DisplayValueTimer = 0;

  }
  if (LoopTask_10Sec) {
    LoopTask_10Sec = OFF;
    if (SampleTime == TASK_10SEC) SD_CardLogTask();

  }
  if (LoopTask_20Sec) {
    LoopTask_20Sec = OFF;
    if (SampleTime == TASK_20SEC) SD_CardLogTask();

  }
  if (LoopTask_60Sec) {
    LoopTask_60Sec = OFF;
    if (SampleTime == TASK_60SEC) SD_CardLogTask();

  }
  
}

void AnalogValRead() {
  // https://www.onlinegdb.com/edit/Hkmlxi_08

  deBugString = "Cur_tRd_1";
#ifdef ARDUINO_MEGA
  ADCSRA |= (1 << ADEN); // enable adc
#endif
  delay(1);
  Current_Mains_Raw = analogRead(4);
  //  Current_Mains_Raw_Trim = Current_Mains_Raw;
  //  delay(1);
  //  239vac -> 4.94vdc
  // 242  vac  5vdc  242/1024 = 0.2363281

  //  238vac -> 3.10vdc  // 33K/8K2
  // 383  vac  5vdc  383/1024 = 0.374874

  CurrentArray[CurrentIndexer] = Current_Mains_Raw;
  CurrentIndexer++;
  if (CurrentIndexer >= 10) {
    CurrentIndexer = 0;
    unsigned int Cumulative = 0;
    for (unsigned int i = 0; i < 10; i++) {
      Cumulative += CurrentArray[i];
    }
#define Volt_Coeff 4.8828125 // rms 5v
#define PeakToRms  1.4142135
    // #define Rms_Coeff  6.90533966  // Volt_Coeff *  PeakToRms
#define Rms_Coeff  4.8828125  // Volt_Coeff *  PeakToRms       
    /*
        Current_MainsAverage = ((Cumulative%10) * Volt_Coeff )/10000;
       // then the decimal part
       Current_MainsAverage += ((float)(Cumulative/10) * Volt_Coeff )/1000;
    */
    Current_Mains_Rms = ((Cumulative % 10) * Rms_Coeff ) / 10000;
    // then the decimal part
    Current_Mains_Rms += ((float)(Cumulative / 10) * Rms_Coeff ) / 1000;

    //   Current_Mains_Rms = Current_MainsAverage * 1.414213;
    //   Current_Mains_Av = Current_Mains_Rms / 1,11;
    //  Current_MainsAverage = ((float)Cumulative * 5.044)/1000; // 2K2 // 4.7K // 2K2
    //   Current_MainsAverage = ((float)Cumulative * 9.766)/1000;  //direct
  }

  //  Current_Mains = ((float)Current_Mains_Raw * Rms_Coeff)/1000;
  // Current_Mains *= PeakToRms;

  //   Current_Mains = ((float)Current_Mains_Raw * 5.044)/1000;
  //   Current_Mains = ((float)Current_Mains_Raw * 9.766)/1000; // direct no voltage divider
  Mains_Volt_Raw =  analogRead(1);
  Mains_Volt =   (unsigned int)((float)Mains_Volt_Raw * 0.374874);

#ifdef ARDUINO_MEGA
  ADCSRA &= ~ (1 << ADEN);            // turn off ADC
#endif
  deBugString = "Cur_tRd_2";
}

void SDS_DustSensor(void) {
#ifdef PM25_DUST_SENSOR_EXISTS
/*
  PmResult pm = sds.queryPm();
  
  //   PmResult pm = sds.readPm();
  if (pm.isOk()) {
    Values.PM25 = pm.pm25;
    Values.PM10 = pm.pm10;
    if (Values.PM25 >= 250.0)Values.PM25 = 250.0;
    if (Values.PM10 >= 250.0)Values.PM25 = 250.0;

    // if you want to just print the measured values, you can use toString() method as well
      Serial.println(pm.toString());
    
  } else {
    Serial.print("Pm2.5 Problem: ");
 //   Serial.println(pm.statusToString());
  }
    */
#endif

}

void WindSensorRead() {
  /*
     #ifdef ARDUINO_MEGA
    ADCSRA |= (1 << ADEN); // enable adc
         #endif
    delay(1);
    //  Values.WindRaw = analogRead(2);delay(1);
    Values.WindMPH = analogRead(OUT_PINOUT);delay(1);
    Values.WindTemp = analogRead(TMP_PINOUT);
    WindSpeed_Calculation();
    #ifdef ARDUINO_MEGA
    ADCSRA &= ~ (1 << ADEN);            // turn off ADC
    #endif
  */
}


void KeyTimeOutCheck(void) {
  if (KeyBoardTimeOutEnb == ON) {
    if (KeyBoardTimeOut)KeyBoardTimeOut--;
    else {
      KeyBoardTimeOutEnb = OFF;
      Menu =  MENU_NULL;
    }
  }
}


void KeyTimeOutStart(void) {
  KeyBoardTimeOutEnb = ON;
  KeyBoardTimeOut  = 24;// 24 sec
}



void DisplayWakeUp(void) {
  if ((OLED_Timer == 0) && (OLED_Init == OFF)) {
    OLED_Init = ON;
  }//else if(OLED_Timer)OLED_Timer += 10; // add additional time every time any key released
}

void Key_Functions(void) {
  if (!KeyLeft_Rel && !KeyMid_Rel && !KeyRight_Rel) {
    KeyReleased = ON;
  }
  if (KeyReleased && !digitalRead(KEY_LEFT)) {
    KeyLeft_Rel = ON;
#ifdef DEBUG_KEY
    KeyLogger = 1;
#endif
    return;
  }
  if (KeyLeft_Rel  &&  digitalRead(KEY_LEFT)) {
    KeyLeft_Rel = OFF;
#ifdef DEBUG_KEY
    KeyLogger = 2;
#endif
    DisplayWakeUp();
    EnterMenuKey();
    KeyTimeOutStart();
    return;
  }
  if (KeyReleased && !digitalRead(KEY_MID)) {
    KeyMid_Rel = ON;
#ifdef DEBUG_KEY
    KeyLogger = 3;
#endif
    return;
  }
  if (KeyMid_Rel  &&  digitalRead(KEY_MID)) {
    KeyMid_Rel = OFF;
#ifdef DEBUG_KEY
    KeyLogger = 4;
#endif
    DisplayWakeUp();
    DownMenuKey();
    KeyTimeOutStart();
    return;
  }
  if (KeyReleased && !digitalRead(KEY_RIGHT)) {
    KeyRight_Rel = ON;
#ifdef DEBUG_KEY
    KeyLogger = 5;
#endif
    return;
  }
  if (KeyRight_Rel  &&  digitalRead(KEY_RIGHT)) {
    KeyRight_Rel = OFF;
#ifdef DEBUG_KEY
    KeyLogger = 6;
#endif
    DisplayWakeUp();
    EscMenuKey();
    KeyTimeOutStart();
    return;

  }
}


void DispEnable(bool Enable) {
  if (Enable == ON) {
    DisplaySleepEnable = ON; //go sleep
    OLED_Timer = 20;
  }
  else   DisplaySleepEnable = OFF;    // no sleep
}

void LogEnable(bool Enable) {
  /*
    if(Enable == ON)LogPause = ON;
    else{
    LogPause = OFF;SD_KartStop = OFF;// once to get sd kart info only
    }
  */
}




void  DispExtTimeout(void) {
  if (OLED_Timer <= KEYDISP_TIMER) OLED_Timer = KEYDISP_TIMER;
}
void UpdateInfoQue(void){
     DispRollIndex[3] = DispRollIndex[2];
     DispRollIndex[2] = DispRollIndex[1];
     DispRollIndex[1] = DispRollIndex[0];
     DispRollIndex[0]++;
     if (DispRollIndex[0]  > 7) DispRollIndex[0] = 1;
}
void UpdateDispRoll(void){
    if(SensorRollTimer){
      SensorRollTimer--;
      return;
    }
    UpdateInfoQue();

}
void KeySensonsorRoll(){
      SensorRollTimer = 20;
      UpdateInfoQue();      
}

void DownMenuKey(void) {
  if (OLED_Timer == 0) return;
  DispExtTimeout();
  switch (Menu) {
    case MENU_NULL :// Menu = MENU_NULL;
            KeySensonsorRoll();
    
      break;
    case MENU1 : Menu = MENU3; //
      break;
    case MENU2 : Menu = MENU1;
      break;
    case MENU3 : Menu = MENU2;
      break;


    case MENU1_SUB1 :  Menu =  MENU1_SUB2;//
      break;
    case MENU1_SUB2 : Menu =  MENU1_SUB1;//
      break;

    case MENU2_SUB1 :  Menu =  MENU2_SUB7;//
      break;
    case MENU2_SUB2 :  Menu =  MENU2_SUB1;//
      break;
    case MENU2_SUB3 :  Menu =  MENU2_SUB2;//
      break;
    case MENU2_SUB4 :  Menu =  MENU2_SUB3;//
      break;
    case MENU2_SUB5 :  Menu =  MENU2_SUB4;//
      break;
    case MENU2_SUB6 :  Menu =  MENU2_SUB5;//
      break;
    case MENU2_SUB7 :  Menu =  MENU2_SUB6;//
      break;
      //   case MENU2_SUB8 :  Menu =  MENU2_SUB7;//
      break;

    case MENU3_SUB1 :  Menu =  MENU3_SUB2;//
      break;
    case MENU3_SUB2 :  Menu =  MENU3_SUB1;//
      break;


    default: Menu = MENU_NULL;

  }
}

void UpMenuKey(void) {
  if (OLED_Timer == 0) return;
  DispExtTimeout();
  switch (Menu) {
    case MENU_NULL : Menu = MENU_NULL;
      break;
    case MENU1 : Menu = MENU2; //
      break;
    case MENU2 : Menu = MENU3;
      break;
    case MENU3 : Menu = MENU1;
      break;


    case MENU1_SUB1 :  Menu =  MENU1_SUB2;//
      break;
    case MENU1_SUB2 : Menu =  MENU1_SUB1;//
      break;

    case MENU2_SUB1 :  Menu =  MENU2_SUB2;//
      break;
    case MENU2_SUB2 :  Menu =  MENU2_SUB3;//
      break;
    case MENU2_SUB3 :  Menu =  MENU2_SUB4;//
      break;
    case MENU2_SUB4 :  Menu =  MENU2_SUB5;//
      break;
    case MENU2_SUB5 :  Menu =  MENU2_SUB6;//
      break;
    case MENU2_SUB6 :  Menu =  MENU2_SUB7;//
      break;
    case MENU2_SUB7 :  Menu =  MENU2_SUB1;//
      break;
      //  case MENU2_SUB8 :  Menu =  MENU2_SUB1;//
      break;

    case MENU3_SUB1 :  Menu =  MENU3_SUB2;//
      break;
    case MENU3_SUB2 :  Menu =  MENU3_SUB1;//
      break;


    default: Menu = MENU_NULL;

  }
}


void EscMenuKey(void) {
  if (OLED_Timer == 0) return;
  DispExtTimeout();
  switch (Menu) {
    case MENU_NULL : Menu = MENU_NULL;
      break;
    case MENU1 : Menu = MENU_NULL; //
      break;
    case MENU2 : Menu = MENU_NULL;
      break;
    case MENU3 : Menu = MENU_NULL;
      break;


    case MENU1_SUB1 :  Menu =  MENU1;//
      break;
    case MENU1_SUB2 : Menu =  MENU1;//
      break;

    case MENU2_SUB1 :  Menu =  MENU2;//
      break;
    case MENU2_SUB2 : Menu =  MENU2;//
      break;
    case MENU2_SUB3 :  Menu =  MENU2;//
      break;
    case MENU2_SUB4 : Menu =  MENU2;//
      break;
    case MENU2_SUB5 :  Menu =  MENU2;//
      break;
    case MENU2_SUB6 :  Menu =  MENU2;//
      break;
    case MENU2_SUB7 :  Menu =  MENU2;//
      break;
      // case MENU2_SUB8 :  Menu =  MENU2;//
      break;

    case MENU3_SUB1 :  Menu =  MENU3;//
      break;
    case MENU3_SUB2 :  Menu =  MENU3;//
      break;


    default: Menu = MENU_NULL;

  }
}



void EnterMenuKey(void) {
  if (OLED_Timer == 0) return;
  DispExtTimeout();
  switch (Menu) {
    case MENU_NULL : Menu = MENU1;

      break;
    case MENU1 : //Menu = MENU1MIN; // go to sub menu  // sd kart log on
      if (SDCard.LogStatus == ON) Menu = MENU1_SUB2; //already logging
      else  Menu = MENU1_SUB1;
      break;
    case MENU2 : // Menu = MENU2MIN; // call the right menu according to current one
      switch (SampleTime) {
        case TASK_500MSEC: Menu = MENU2_SUB1;
          break;
        case TASK_1SEC : Menu = MENU2_SUB2;
          break;
        case TASK_2SEC : Menu = MENU2_SUB3;
          break;
        case TASK_5SEC : Menu = MENU2_SUB4;
          break;
        case TASK_10SEC : Menu = MENU2_SUB5;
          break;
        case TASK_20SEC : Menu = MENU2_SUB6;
          break;
        case TASK_60SEC : Menu = MENU2_SUB7;
          break;
        default:
          break;
      }
      break;
    case MENU3 : // Menu = MENU3MIN;

      if (DisplaySleepEnable == ON) Menu = MENU3_SUB2; //already logging
      else  Menu = MENU3_SUB1;
      break;


    case MENU1_SUB1 :  LogEnable(ON); SDCard.LogStatus = ON; EESetResetLog(ON);
      Menu =  MENU_NULL;//MENU1
      break;
    case MENU1_SUB2 : LogEnable(OFF); SDCard.LogStatus = OFF; EESetResetLog(OFF); // default
      Menu =  MENU_NULL;//MENU1
      break;
    case MENU2_SUB1 :  SampleTime = TASK_500MSEC ; EESetSampleTimeLog(TASK_500MSEC);
      Menu =  MENU_NULL;//MENU2;//
      break;
    case MENU2_SUB2 : SampleTime = TASK_1SEC; EESetSampleTimeLog(TASK_1SEC);
      Menu =  MENU_NULL;//MENU2;//
      break;
    case MENU2_SUB3 :  SampleTime = TASK_2SEC; EESetSampleTimeLog(TASK_2SEC);
      Menu =  MENU_NULL;//MENU2;//
      break;
    case MENU2_SUB4 : SampleTime = TASK_5SEC; EESetSampleTimeLog(TASK_5SEC); // default
      Menu =  MENU_NULL;//MENU2;//
      break;
    case MENU2_SUB5 :  SampleTime = TASK_10SEC; EESetSampleTimeLog(TASK_10SEC);
      Menu =  MENU_NULL;//MENU2;//
      break;
    case MENU2_SUB6 :  SampleTime = TASK_20SEC; EESetSampleTimeLog(TASK_20SEC);
      Menu =  MENU_NULL;//MENU2;//
      break;
    case MENU2_SUB7 :  SampleTime = TASK_60SEC; EESetSampleTimeLog(TASK_60SEC);
      Menu =  MENU_NULL;//MENU2;//
      break;
    case MENU3_SUB1 :  DispEnable(ON);
      Menu =  MENU_NULL;//MENU3
      break;
    case MENU3_SUB2 :  DispEnable(OFF);
      Menu =  MENU_NULL;//MENU3
      break;


    default: Menu = MENU_NULL;

  }
}


void EE_SerNoWrite2_EE(unsigned int SerialNo) {
  //  EEPROM.write(Adr, byte);
  // byte t = 0XFFFF & (SerialNo>>8);
  byte t;
  t = (byte)SerialNo;
  EEPROM.write(4, t);// low byte
  t = (byte)(SerialNo >> 8);
  EEPROM.write(5, t);// high byte

}

void EESetResetLog(bool Mode) {
  if (Mode == OFF)EEPROM.write(ADDRES_LOG, OFF); // OFF
  else EEPROM.write(ADDRES_LOG, SampleTime);// ON
}
void EESetSampleTimeLog(byte Sample) {
  EEPROM.write(ADDRES_LOG, Sample);// ON
}


void EEReadLog(void) {
  byte Mode = EEPROM.read(ADDRES_LOG);// OFF
  switch (Mode) {
    case TASK_500MSEC: SDCard.LogStatus = ON; SampleTime =  Mode;
      break;
    case TASK_1SEC : SDCard.LogStatus = ON; SampleTime =  Mode;
      break;
    case TASK_2SEC : SDCard.LogStatus = ON; SampleTime =  Mode;
      break;
    case TASK_5SEC : SDCard.LogStatus = ON; SampleTime =  Mode;
      break;
    case TASK_10SEC : SDCard.LogStatus = ON; SampleTime =  Mode;
      break;
    case TASK_20SEC : SDCard.LogStatus = ON; SampleTime =  Mode;
      break;
    case TASK_60SEC : SDCard.LogStatus = ON; SampleTime =  Mode;
      break;
    default: SDCard.LogStatus = OFF; SampleTime =  TASK_2SEC;
      break;
  }
}
void UpdateDeviceEE() {
  char c;
  EE_Id_EString = "";
  c = (char)EEPROM.read(4);
  EE_Id_EString += String(c);
  c = (char)EEPROM.read(5);
  EE_Id_EString += String(c);
  c = (char)EEPROM.read(6);
  EE_Id_EString += String(c);
  c = (char)EEPROM.read(7);
  EE_Id_EString += String(c);
  Serial.print(" Device Id: ");
  Serial.println(EE_Id_EString);
}
void ResetCasePrint() {
  byte RESET_CASE = MCUSR;
  Serial.print("MCUSR: ");
  Serial.println(RESET_CASE);
  if (MCUSR & WDRF) {
    Serial.print("Rebooting from a Watchdog Reset");
  }
  else if (MCUSR & BORF) {
    Serial.print("Rebooting from a Brown-out Reset");
  }
  else if (MCUSR & EXTRF) {
    Serial.print("Rebooting from an External Reset");
  }
  else if (MCUSR & PORF) {
    Serial.print("Rebooting from a Power On Reset");
  }
  if (MCUSR & (1 << WDRF)) {
    // a watchdog reset occurred
    Serial.print("Rebooting from a Watchdog Reset");
  }
  if (MCUSR & (1 << BORF)) {
    Serial.print("Rebooting from a Brown-out Reset");
  }
  //  a brownout reset occurred
  if (MCUSR & (1 << EXTRF)) {
    //  an external reset occurred
    Serial.print("Rebooting from an External Reset");
  }
  if (MCUSR & (1 << PORF)) {
    //  a power on reset occurred
    Serial.print("Rebooting from a Power On Reset");
  }
  //Clear register
  MCUSR = 0x00;
}
void IO_Settings() {
  pinMode(53, OUTPUT);  // SS Pin high to avoid miscommunication
  digitalWrite(53, HIGH);

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  pinMode(4, OUTPUT);  // ADE9153A_RESET_PIN
  digitalWrite(4, HIGH);

  pinMode(LED_GREEN, OUTPUT);           // set pin to input
  digitalWrite(LED_GREEN, LOW);       // turn on pullup resistors
  pinMode(LED_RED, OUTPUT);           // set pin to input
  digitalWrite(LED_RED, LOW);       // turn on pullup resistors

  pinMode(KEY_LEFT, INPUT);           // set pin to input
  pinMode(KEY_LEFT, INPUT_PULLUP);

  pinMode(KEY_MID, INPUT);           // set pin to input
  pinMode(KEY_MID, INPUT_PULLUP);

  pinMode(KEY_RIGHT, INPUT);           // set pin to input
  pinMode(KEY_RIGHT, INPUT_PULLUP);


}
void MicroInit() {
  
  Serial.begin(115200);

  IO_Settings();

  ResetCasePrint();

  //  SDCard.LogStatus = 0;      // default start with log off;
  EEReadLog();
  SDCard.LogStatusInit = 0;  // put the header of the csv file

  Serial.print("SDCard.LogStatus: ");
  Serial.print(SDCard.LogStatus);
  Serial.print("    SampleTime: ");
  Serial.println(SampleTime);




  //wdt_enable(WDT0_1S);

#ifdef ARDUINO_MEGA

  wdt_reset();
  wdt_enable(WDTO_8S);
  //https://www.nongnu.org/avr-libc/user-manual/group__avr__watchdog.html

#endif

#ifdef ARDUINO_MEGA
  ADCSRA &= ~ (1 << ADEN);            // turn off ADC to save power ,, enable when needed and turn off again
#endif

  FW_Version = String (__DATE__)  + ' ' +  String ( __TIME__ ), // 11 1 8 // 20
  //  FW_Version.remove(17,3); // Remove from from index=7 through the end of the string
  FW_Version.remove(7, 2); // Remove 2 characters starting at index=7
  FW_Version.setCharAt(3 , '.');
  FW_Version.setCharAt(6 , '.');


  //Serial.println( "Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__);
  //Compiled: Jul 21 2020 15:55:39 7.3.0

  //  ShowSerialCode();
  UpdateDeviceEE();
  Serial.print("EE_Id_EString: ") ;
  Serial.print(EE_Id_EString.charAt(0));
  Serial.print(EE_Id_EString.charAt(1));
  Serial.print(EE_Id_EString.charAt(2));
  Serial.print(EE_Id_EString.charAt(3));
  Serial.println() ;

  // String LOG_FILE =  "LOG_xxxx.csv";
  // Rename Log File with the device Id
  LOG_FILE.setCharAt(4, EE_Id_EString.charAt(0));
  LOG_FILE.setCharAt(5, EE_Id_EString.charAt(1));
  LOG_FILE.setCharAt(6, EE_Id_EString.charAt(2));
  LOG_FILE.setCharAt(7, EE_Id_EString.charAt(3));

  Serial.print("LOG_FILE: ") ;
  Serial.print(LOG_FILE);
  Serial.println() ;


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
