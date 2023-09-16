const int kPinLed = 10;
int delayTime = 1000;
 void setup()
 {
  pinMode(kPinLed, OUTPUT);
 }

void loop()
{

 if(delayTime <= 0){ // If the delay time is zero or less, reset it.
   delayTime = 1000;
 }else{
   delayTime = delayTime - 100;
 }
 digitalWrite(kPinLed, HIGH);
 delay(delayTime);
 digitalWrite(kPinLed, LOW);
 delay(delayTime);
}
