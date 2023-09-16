const int kPinSpeaker = 9;
const int k_timeDelay = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(kPinSpeaker, OUTPUT);
}

void loop()
{
  digitalWrite(kPinSpeaker,HIGH);
  delayMicroseconds(k_timeDelay);
  digitalWrite(kPinSpeaker,LOW);
  delayMicroseconds(k_timeDelay);
}
