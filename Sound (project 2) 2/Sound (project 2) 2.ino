const int kPinSpeaker = 9;
const int kPinButton1 = 2;
const int kPinButton2 = 3;
#include "beats.h"



void setup()
{
  pinMode(kPinButton1, INPUT);
  pinMode(kPinButton2, INPUT);
  pinMode(kPinSpeaker, OUTPUT);
  digitalWrite(kPinButton1, LOW);
  digitalWrite(kPinButton2, LOW);
}

void loop()
{
if(digitalRead(kPinButton1) == HIGH)
 {
  ourTone(300,NOTE_C4);
  ourTone(50, noTone);
  ourTone(300,NOTE_C4);
  ourTone(600,NOTE_D4);
  ourTone(300,NOTE_C4);
  ourTone(600,NOTE_F4);
  ourTone(1200,NOTE_E4);
  noTone(kPinSpeaker);
  delay(2000);
  }
if(digitalRead(kPinButton2)== HIGH) {
  ourTone(1200,NOTE_E4);
  ourTone(600,NOTE_F4);
  ourTone(300,NOTE_C4);
  ourTone(600,NOTE_D4);
  ourTone(300,NOTE_C4);
  ourTone(50, noTone);
  ourTone(300,NOTE_C4);
  noTone(kPinSpeaker);
  delay(2000);
  }
}  

void ourTone(int delayT, int freq){
  tone(kPinSpeaker, freq);
  delay(delayT);
}
