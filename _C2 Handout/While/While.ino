const int kPinLed = 13;
int delayTime = 0;
 void setup()
 {
  pinMode(kPinLed, OUTPUT);
 }

void loop()
{
  while(delayTime < 1000){ // while delayTime is less than 1000
   delayTime = delayTime + 100; 
   digitalWrite(kPinLed, HIGH);
   delay(delayTime);
   digitalWrite(kPinLed, LOW);
   delay(delayTime);
  }
  delayTime = 0;

}
