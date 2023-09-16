#include <stdio.h>
#include <DS1302.h>
#include <LiquidCrystal.h>
#include <dht11.h>
#include "pitches.h"

#define CLEAR 0
#define SET 1
#define ON 1
#define OFF 0
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

dht11 DHT11;
#define DHT11Pin 2

int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define DISP_NORM 0
#define DISP_SONG 1
#define DISP_ALRM 2
unsigned char MenuNum = DISP_NORM;
unsigned char chatTime=0;

// LCD charcater
char msg1[16];  // Row 1
char msg2[16];  // Row 2
char msgbuf1[16]; 
char msgbuf2[16];

unsigned char timer25ms = CLEAR; // timer
unsigned long lastimer = CLEAR;  // last record time
unsigned char timer1000ms = CLEAR;
unsigned char timer1000cnt = CLEAR;
unsigned char timer100ms = CLEAR;
unsigned char timer100cnt = CLEAR;
unsigned int counter = CLEAR;

const int kCePin   = 12;  // Chip Enable
const int kIoPin   = 3;  // Input/Output
const int kSclkPin =11;  // Serial Clock

const int PowerPin = 13;

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);
Time t = rtc.time();
// working variable for clock
unsigned char second=0;
unsigned char minute=0;
unsigned char hour=0;
unsigned char month=0;
unsigned int year=0;
unsigned char dayOfWeek =0;
unsigned char dayOfMonth=0;

unsigned char toggle=0;
#define kPinSpeaker  0
#define SpeakerGnd 1
/***************************************************************/
/* Setia */

const int beat_length = 200;  // beat waiting time
unsigned char StartSong = 0;
unsigned int SongDelay = 0;
unsigned int SongBeatCnt = 0; // Song1 Beat counter
unsigned int SongBeatNum =0;  // Song1 Beat number
unsigned char flagNoSound = 1;
const int SongNotes[] = // 0 represents a rest
{
 N_E6,N_E6,N_D6, N_D6,N_C6,N_C6,N_B5,  N_B5,N_A5,N_A5,N_G5,  N_G5,0,N_G5,N_C6,N_B5, N_C6,N_G5,0,N_G5,N_C6,N_B5,
 N_C6,N_G5,0,N_G5,N_C6,N_B5, N_C6,N_C6,N_C6,N_A5,N_A5,N_G5,  0,N_G5,N_C6,N_B5, N_C6,N_G5,0,N_G5,N_E6,N_D6, N_D6,N_C6,0,N_G5,N_C6,N_B5,
 N_C6,N_A5,N_A5,N_A5,N_A5,N_C6,N_A6,N_G6, 0, N_D6,N_D6,N_F6, N_F6,N_E6,N_E6,0,N_E6,N_E6,N_B5, N_D6,N_C6,N_C6,N_B5,N_C6,N_C6,N_B5,N_C6,
 N_F6,0,N_G5,N_G6,N_F6,N_E6,N_D6, 0,N_D6,N_D6,N_F6, N_F6,N_E6,N_E6,0,N_E6,N_B6,N_B6, N_B6,N_A6,N_B6,N_C7,N_C7,N_D6,N_C6,
 N_A6,0,N_A6,N_A6,N_G6,N_G6,N_G6, 0,N_G6,N_G6,N_F6, N_E6,N_E6,N_F6,N_E6,N_E6,N_F6, N_E6,N_F6,N_E6,N_D6,N_C6,N_C6,N_E6,N_G6,
 N_A6,N_A6,N_A6,N_G6,N_D6,N_E6,N_F6, N_E6,0,N_C6,N_E6,N_G6, N_A6,N_A6,N_A6,N_G6,N_D6,N_E6,N_F6, N_E6,N_F6,N_E6,N_D6,N_C6,N_D6,N_E6,
 N_A5,N_A5,N_C6,N_C6,N_B5, N_C6,0,N_D6,N_E6,  N_A5,N_A5,N_C6,N_C6,N_B5, N_C6,0,
 0
};

const unsigned char SongBeats[] = 
{
 6,1,1,  3,3,1,1, 2,4,1,1, 4,1,1,1,1, 2,2,1,1,1,1,
 2,2,1,1,1,1, 3,1,1,1,1,3, 3,1,1,1, 2,2,1,1,1,1, 2,2,1,1,1,1,
 1,1,1,1,1,1,1,3, 3,1,1,1, 1,1,2,1,1,1,1, 1,1,1,1,1,1,1,1,
 2,1,1,1,1,1,3, 3,1,1,1, 1,1,2,1,1,1,1, 1,1,1,2,1,1,1,
 2,1,1,1,1,1,3, 3,1,1,1, 2,1,1,2,1,1, 1,1,1,1,1,1,1,1,
 2,1,1,1,1,1,1, 2,3,1,1,1,  2,1,1,1,1,1,1, 1,1,1,1,2,1,1,
 2,1,1,2,2, 2,4,1,1, 2,1,1,2,2, 2,6,
 10
};
void setup() {
  int i = 0;
 // Serial.begin(9600);
  lcd.begin(16, 2);     
  lcd.setCursor(0,0);
  for (i=0; i<16; i++){
    msg1[i] = CLEAR;
    msg2[i] = CLEAR;
  }

  pinMode(PowerPin, OUTPUT);
  digitalWrite(PowerPin, HIGH);
  pinMode(kPinSpeaker, OUTPUT);
  pinMode(SpeakerGnd, OUTPUT);
  digitalWrite(SpeakerGnd, LOW);
  StartSong = CLEAR;
  SongBeatCnt = 0;
  SongBeatNum = sizeof(SongBeats);
               
  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  rtc.writeProtect(false);
  rtc.halt(false);
  // Make a new time object to set the date and time.
  // Year, Month, Date  Hour Min Sec 

 // set the latest time here
 // Time t(2021, 05, 31, 10, 05, 00, Time::kMonday);

 // Set the time and date on the chip.
 //  rtc.time(t);
}

void timer(void)
{
  unsigned long data;
  timer25ms=CLEAR;
  timer100ms = CLEAR;
  timer1000ms = CLEAR;
  data = millis();
  if ((data-lastimer)>=25){
    timer25ms = SET;
    if(++timer100cnt>=4){
      timer100ms = SET;
      timer100cnt = CLEAR;
    }
    if(++timer1000cnt>=40){
      timer1000ms = SET;
      timer1000cnt = CLEAR;
    }
    lastimer = millis();  
  }
}

void loop() {
  timer();
  if(timer25ms){
    SongPlayControl(); 
  }  
  if(timer100ms){
     ReadTime();
     ReadDHT();
     AdKeyControl();
     DispControl();
     LCDDispControl();
  }
  if(timer1000ms){
     DHTDisplay();
  }
  
}

void ReadDHT(){
  int chk = DHT11.read(DHT11Pin);
}
void LCDDispControl(void)
{
  LCDPutChar1();
  LCDPutChar2(); 
}  

void LCDPutChar1()
{
  char i;
  for (i=0;i<16;i++){
     if (msg1[i] != msgbuf1[i]){
       msgbuf1[i] = msg1[i];
       lcd.setCursor(i,0);
       lcd.print(msgbuf1[i]);
     }
  }
}

void LCDPutChar2()
{
  char i;
  
  for (i=0;i<16;i++){
    if (msg2[i] != msgbuf2[i]){
     msgbuf2[i] = msg2[i];
      lcd.setCursor(i,1);
      lcd.print(msgbuf2[i]);
    }
  }
}

String dayAsString(const Time::Day day) {
  dayOfWeek = day-1;  // SUN : 0, MON : 1.... SAT : 6
}

void ReadTime() {
 Time t = rtc.time();
  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
// Get clcok info
  second = t.sec;
  minute = t.min;
  hour = t.hr;
  dayOfMonth = t.date;
  month = t.mon;
  year = t.yr;
}
const char OnOff[2][3]{ "ON ", "OFF"};

const char Day[7][3]{ "SUN",
                    "MON",
                    "TUE",
                    "WED",
                    "THU",
                    "FRI",
                    "SAT"};    

const char Month[12][3]{ "JAN",
                         "FEB",
                         "MAR",
                         "APR",
                         "MAY",
                         "JUN",
                         "JUL",
                         "AUG",
                         "SEP",
                         "OCT",
                         "NOV",
                         "DEC"};

void DHTDisplay(){
  if(toggle) {
    TempDisplay();
    toggle=0;
  }else{
    HumidDisplay();
    toggle=1;
  }
}     

void TempDisplay(){
  int data =0;
  char TempMsg[] ="Temperature:";
  for(int i=0; i<12; i++){
    msg2[i]=TempMsg[i];
  }
  data = DHT11.temperature;  // cconvert to 1 decimal
  msg2[12]=(data/10)+48;
  msg2[13]=(data%10)+48;
  msg2[14]=0x20;
  msg2[15]='C';
}
void HumidDisplay(){
  int data =0;
  char HumMsg[] ="  Humidity :";
  for(int i=0; i<12; i++){
    msg2[i]=HumMsg[i];
  }
  data = DHT11.humidity;  // cconvert to 1 decimal
  msg2[12]=(data/10)+48;
  msg2[13]=(data%10)+48;
  msg2[14]=0x20;
  msg2[15]='%';
}
                      
void ClockDisplay(){
   int i=0;
  if(dayOfMonth < 10){
      msg1[0] = ' ';
      msg1[1] = dayOfMonth+48;
  }else{
     msg1[0] = (dayOfMonth/10)+48;
     msg1[1] = (dayOfMonth%10)+48;
  }
  msg1[2] = 0x20;;
  for (int i=0; i<3; i++){
    msg1[3+i] = Day[dayOfWeek][i];
  }
  msg1[6] = 0x20;
  if(hour < 10){
    msg1[7] = '0';
    msg1[8] = hour+48;
  }else{
    msg1[7] = (hour/10)+48;
    msg1[8] = (hour%10)+48;
  }
  msg1[9] = ':';
  if(minute<10){
    msg1[10] ='0';
    msg1[11] = minute+48;
  }else{
    msg1[10] = (minute/10)+48;
    msg1[11] = (minute%10)+48;
  }
  msg1[12] = ':';
  if(second<10){
    msg1[13] = '0';
    msg1[14] = second+48;
  }else{
    msg1[13] = (second/10)+48;
    msg1[14] = (second%10)+48;
  }
   msg1[15] = ' ';
}

//Read Analog input
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);          // Read from Analog pin 0 
 // AD Value read from 5 port ：0,93,229,380,628
 // Threshold setting as 46,165,310,504,704
 if (adc_key_in > 1000) return btnNONE; 
 if (adc_key_in < 46)   return btnRIGHT;  
 if (adc_key_in < 165)  return btnUP; 
 if (adc_key_in < 310)  return btnDOWN; 
 if (adc_key_in < 504)  return btnLEFT; 
 if (adc_key_in < 800)  return btnSELECT;  
 return btnNONE; 
}

void AdKeyControl(){
  if(chatTime) chatTime--;
  else{
    chatTime=2;
    lcd_key = read_LCD_buttons();  // Read A/D Key
    if(lcd_key==btnSELECT){
      if(++MenuNum > DISP_ALRM){
        MenuNum = DISP_NORM;  
      }
      StartSong = CLEAR;
      if(MenuNum==DISP_SONG){
        StartSong = SET;
      }
    }
  }  
}

void DispControl(){
  if (MenuNum == DISP_NORM){
    ClockDisplay();
  }else if(MenuNum == DISP_SONG){
    SongDisplay();
  }else if(MenuNum == DISP_ALRM){
    AlarmDisplay();
  }
}

void SongDisplay(){
  char SongName[] = "  <<Dong Hua>>  ";
  for (int i =0; i<16; i++){
    msg1[i] = SongName[i];
  }
}

void AlarmDisplay(){
  char Alarm[] = "ALARM           ";
  for (int i =0; i<16; i++){
    msg1[i] = Alarm[i];
  }
}

void ourTone(int freq, int duration)
{
 tone(kPinSpeaker, freq, duration);
}

void SongPlayControl()
{
  if(StartSong==SET){
    Song1();
  }else{
    SongBeatCnt = CLEAR;
    SongDelay = CLEAR;
    flagNoSound = SET;
    noTone(kPinSpeaker);  
  }
}

void Song1(void)
{
 
  if(SongDelay){
    SongDelay = SongDelay - 25;
  }else{
     if (SongBeatCnt >= SongBeatNum){ // restart song
         SongBeatCnt = 0;
         SongDelay = CLEAR;
     }
     if(flagNoSound == CLEAR){    // Need extra delay time
      noTone(kPinSpeaker);
      SongDelay = 50;
      flagNoSound = SET;
      if (SongBeatCnt < SongBeatNum){
         SongBeatCnt = SongBeatCnt + 1;
      }else{
         SongBeatCnt = 0;
         SongDelay = CLEAR;
      }
    }else if (SongNotes[SongBeatCnt] == 0) {    // short notes
      SongDelay = (SongBeats[SongBeatCnt] * beat_length);
      noTone(kPinSpeaker);
      flagNoSound = SET;
      if (SongBeatCnt < SongBeatNum){
         SongBeatCnt = SongBeatCnt + 1;
      }else{
         SongBeatCnt = 0;
         SongDelay = CLEAR;
      }
    }else {
      flagNoSound = CLEAR;
      SongDelay = SongBeats[SongBeatCnt]*beat_length;
      ourTone(SongNotes[SongBeatCnt], SongDelay);
    }
  }  
}  
