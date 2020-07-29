

// C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries
// Location of Main Librarires

// Set Origin
//   git remote add origin git@github.com:ilkerya/Pangolin.git
//  https://github.com/ilkerya/Pangolin
//  https://blog.plover.com/prog/git-ff-error.html
// C:\Users\Yagciilk\Documents\Arduino\libraries
// C:\Program Files (x86)\Arduino\libraries   
// C:\Projects\Pangolin\Pangolin\ArduinoCore\include  default AtmelStudio Project lib locations
/*
git add .
git commit -m "Comment"
git push https://github.com/ilkerya/Pangolin.git master
*/
 #define SI072_FIRST_SENSOR 7  // multiplexer Channel 7 first blu box prot
 #define SI072_SECOND_SENSOR 1 // first prot  0      0
 #define SI072_THIRD_SENSOR 2 // sec1                2 

#define NO_IC2_MULTIPLEXER 16

#define TEMP_HUM_1_SENSOR_EXISTS
#define TEMP_HUM_2_SENSOR_EXISTS
#define TEMP_HUM_3_SENSOR_EXISTS  
//#define LIGHT_SENSOR_EXISTS  
//#define BAR_PRES_SENSOR_EXISTS  
//#define ACCL_GYRO_SENSOR_EXISTS  
//#define WIND_SENSOR_EXISTS  
#define LEM_CURRENT_EXISTS
#define VOLTAGE_MEASURE_EXISTS
#define PM25_DUST_SENSOR_EXISTS

#define  MAXSHOWLINE 6  // define how many lines for sensorts to show including fw info line 

#define DEBUG_KEY
#define LED_GREEN 3// 11//3 // GREEN
#define LED_RED 4 // 12//4 //RED

#define CS_PIN 8              //8-->Arduino Zero. 15-->ESP8266 

#define ON 1 //
#define OFF 0 //
#define KEY_LEFT 6//13//6 // ok
#define KEY_MID 5// 11//5 //
#define KEY_RIGHT 2//12//2 //

#define MENU_NULL 0
#define MENU1   32
#define MENU2   64
#define MENU3   96

#define MENU_MAINMIN  32
#define MENU_MAINMAX  96

#define MENU_MAIN11 32  // +=32
#define MENU_MAIN11 64
#define MENU_MAIN11 96

#define MENU1MIN  36
#define MENU1MAX  40

#define MENU1_SUB1 36 // +=4
#define MENU1_SUB2 40


#define MENU2MIN  68
#define MENU2MAX  92

#define MENU2_SUB1  68  // +=4
#define MENU2_SUB2  72
#define MENU2_SUB3  76
#define MENU2_SUB4  80
#define MENU2_SUB5  84
#define MENU2_SUB6  88
#define MENU2_SUB7  92
//#define MENU2_SUB8  96



#define MENU3MIN  100
#define MENU3MAX  104


#define MENU3_SUB1  100 // +=4
#define MENU3_SUB2  104

#define KEYDISP_TIMER 20

#define OUT_PINOUT 2 // Out pin of the sensor
#define RV_PINOUT 1 // RV output of the sensor
#define TMP_PINOUT 0 // TMP pin of sensor this is temperature output


// function prototypes
void Common_Loop(); 
void ResetCasePrint();
void IO_Settings();
void MicroInit(void);
void Display_ReInit(byte Timer);
void  RTC_Init();
void  SensorInit_Si072(byte);
void  SensorAlt_Init();
void  SensorLight_Init();
void  SensorACccel_GyroInit();
void  Sensors_PeripInit();

void AnalogValRead();
void  AdcRead();
void WindSensorRead();
void  SensorRead_Si072();
void  SensorAlt_Read();
void  SensorLight_Read();
void  SensorAcccel_GyroRead();
void SDS_DustSensor(void);
void UpdateSensorInfo(void);
void EE_SerNoWrite2_EE(unsigned int SerialNo);
void UpdateDeviceEE();
void UpdateInfoLine();
void UpdateDisplayMenu();
void UpdateSD_LogTime();
void UpdateFileSize();
void UpdateProperLine(byte Index, byte Line);

void EscMenuKey(void);
void EnterMenuKey(void);
void DownMenuKey(void);
void UpMenuKey(void);
void SetSampling(unsigned int Time);
void DispEnable(bool Enable);
void LogEnable(bool Enable);
void  DispExtTimeout(void);
void   DisplayMenu(void);
void KeyTimeOutCheck(void);
void SD_CardLogTask(void);
void SD_Log_File(void);
void SD_Info_Only(void);
void DisplayFullSensors(void);
void DisplayTestDevices(void);
void SerialPortRx(void);
void UpdateDispRoll(void);


/*
First Time
git init
git add README.md


GitHub Bash Commands
Adding new file
https://help.github.com/articles/adding-a-file-to-a-repository-using-the-command-line/#platform-windows

git add .

git commit -m "Add existing file"

// For Common git
git push https://github.com/ilkerya/Pangolin master

// For Electrolux git
git push  http://git.int.electrolux.com/ilkerya/Phoenix_Pangolin.git master


https://help.github.com/articles/fetching-a-remote/


http://git.int.electrolux.com/ilkerya/Phoenix_Mobile.git


In case in the first push gives error use below command

git remote add origin remote repository URL
git push origin master

git push https://github.com/ilkerya/Phoenix master --force
*/
