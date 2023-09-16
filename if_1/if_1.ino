const int kPinLed = 10;
int delayTime = 0;
 void setup()
 {
  pinMode(kPinLed, OUTPUT);
 }

void loop()
{

 if(delayTime >= 1000){ // If the delay time is zero or less, reset it.
   delayTime = 0;
 }else{
   delayTime = delayTime + 100;
 }
 digitalWrite(kPinLed, HIGH);
 delay(delayTime);
 digitalWrite(kPinLed, LOW);
 delay(delayTime);
}
