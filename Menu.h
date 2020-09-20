
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






void  DispExtTimeout(void) {
  if (OLED_Timer <= KEYDISP_TIMER) OLED_Timer = KEYDISP_TIMER;
}
void UpdateInfoQue(void){
     DispRollIndex[3] = DispRollIndex[2];
     DispRollIndex[2] = DispRollIndex[1];
     DispRollIndex[1] = DispRollIndex[0];
     DispRollIndex[0]++;
     if (DispRollIndex[0]  > 9) DispRollIndex[0] = 1;
}
void UpdateDispRoll(void){
    if(SensorRollTimer){
      SensorRollTimer--;
      return;
    }
    UpdateInfoQue();

}
void KeySensonsorRoll(){
      SensorRollTimer = 30; // 2sec x 30 = 60 sec
      UpdateInfoQue();      
}
void DispEnable(bool Enable, byte Timer) {
  if (Enable == ON) {
    DisplaySleepEnable = ON; //go sleep
    //OLED_Timer = 20;
    OLED_Timer = Timer;
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


void EE_SerNoWrite2_EE(unsigned int SerialNo) {
  //  EEPROM.write(Adr, byte);
  // byte t = 0XFFFF & (SerialNo>>8);
  byte t;
  t = (byte)SerialNo;
  EEPROM.write(4, t);// low byte
  t = (byte)(SerialNo >> 8);
  EEPROM.write(5, t);// high byte

}
void EEDisplaySleepRead(void) {
    byte Mode = EEPROM.read(SLEEP_LOG);// OFF
    if(Mode == OFF)DispEnable(OFF,0);
    if(Mode == ON)DispEnable(ON,100);    
}

void EEDisplaySleep(bool Mode) {
    if (Mode == OFF)EEPROM.write(SLEEP_LOG, OFF); // OFF
    else EEPROM.write(SLEEP_LOG, ON);// ON
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
    case MENU3_SUB1 :  DispEnable(ON,20);EEDisplaySleep(ON);
      Menu =  MENU_NULL;//MENU3
      break;
    case MENU3_SUB2 :  DispEnable(OFF,0);EEDisplaySleep(OFF);
      Menu =  MENU_NULL;//MENU3
      break;
    default: Menu = MENU_NULL;
  }
}
