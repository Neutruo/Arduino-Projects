// Merge Open LCDAdKey

#include <stdio.h>
#include <DS1302.h>
#include <LiquidCrystal.h>
#include <dht11.h>

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

unsigned char timer100ms = CLEAR; // timer
unsigned long lastimer = CLEAR;  // last record time
unsigned char timer1000ms = CLEAR;
unsigned char timer1000cnt = CLEAR;
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

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

const int kPinSpeaker = 9;

timer500ms = 0;

unsigned int delaytimer = 0;

void setup() {
  int i = 0;
  Serial.begin(9600);
  lcd.begin(16, 2);     
  lcd.setCursor(0,0);
  for (i=0; i<16; i++){
    msg1[i] = CLEAR;
    msg2[i] = CLEAR;
  }

  pinMode(PowerPin, OUTPUT);
  digitalWrite(PowerPin, HIGH);
  pinMode(kPinSpeaker, OUTPUT);
               
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
  timer100ms = CLEAR;
  timer1000ms = CLEAR;
  data = millis();
  if ((data-lastimer)>=100){
     timer100ms = SET;
    if(++timer1000cnt>=10){
      timer1000ms = SET;
      timer1000cnt = CLEAR;
    }
    lastimer = millis();  
  }
}

void loop() {
  timer();
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
  if() {
    timer500ms = 1;
  }
  if (timer500ms == 1) {
    timer500ms = 2;
  }
  if (timer500ms == 2) {
    timer500ms = 3;
  }
  if (timer500ms == 3) {
    timer500ms = 4;
  }
  if (timer500ms == 4) {
    timer500ms = 0;
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
  char Song[] = " SONG SELECTION ";
  for (int i =0; i<16; i++){
    msg1[i] = Song[i];
  }
if (timer500ms == 0) {
  tone(kPinSpeaker, NOTE_C4);
}
if (timer500ms == 1) {
  tone(kPinSpeaker, NOTE_D4);
}
if (timer500ms == 2) {
  tone(kPinSpeaker, NOTE_E4);
}
if (timer500ms == 3) {
  tone(kPinSpeaker, NOTE_F4);
}
if (timer500ms == 4) {
  tone(kPinSpeaker, NOTE_G4);
}
}

void AlarmDisplay(){
  char Alarm[] = "ALARM           ";
  for (int i =0; i<16; i++){
    msg1[i] = Alarm[i];
  }

}
