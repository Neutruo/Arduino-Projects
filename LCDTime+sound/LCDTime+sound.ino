int toggle = 1;
const int kPinLed = 13;
const int kPinSpeaker = 11;
#include <LiquidCrystal.h>

#define CLEAR 0
#define SET 1
#define ON 1
#define OFF 0

// Port use for LCD Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

unsigned char timer100ms = CLEAR; // timer
unsigned long lastimer = CLEAR;  // last record time
unsigned char timer1000ms = CLEAR;
unsigned char timer1000cnt = CLEAR;
int counter = 10;

// the setup routine runs once when you press reset:
void setup() {  
 pinMode(kPinLed, OUTPUT); 
 pinMode(kPinSpeaker,OUTPUT);               
 lcd.begin(16, 2);              // Start
 lcd.setCursor(0,0);
 lcd.print("Waiting Time"); 
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

void ourTone() {
  tone(11,100);
}

// the loop routine runs over and over again forever:
void loop() {

  lcd.setCursor(9,1);            // Start from Row 2, space 9
  lcd.print(counter, DEC);      // display waiting time


  timer();
  if(timer1000ms){
    if(--counter < 0){
      counter = 0;
      ourTone();
      lcd.clear();
      if(timer1000ms == SET) {
        toggle = !toggle;
        digitalWrite (kPinLed, toggle);
      }
    }
    lcd.clear();
    lcd.print("Waiting Time"); 
    lcd.setCursor(9,1);            // Start from Row 2, space 9
    lcd.print(counter, DEC);      // display waiting time
  }  
}