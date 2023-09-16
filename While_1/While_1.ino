const int kPinLed = 13;
int delayTime = 1000;
 void setup()
 {
  pinMode(kPinLed, OUTPUT);
 }

void loop()
{
  while(delayTime > 0){ // while delayTime is less than 1000
   delayTime = delayTime - 100; 
   digitalWrite(kPinLed, HIGH);
   delay(delayTime);
   digitalWrite(kPinLed, LOW);
   delay(delayTime);
  }
  delayTime = 1000;

}
