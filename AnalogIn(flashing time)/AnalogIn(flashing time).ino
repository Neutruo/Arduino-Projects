const int kPinPot = A0;
const int kPinLed = 9;
int flashing = 0;
int sensorValue = 0;
void setup() {
  pinMode(kPinPot, INPUT);
  pinMode(kPinLed, OUTPUT);

}

void loop() {
  sensorValue = analogRead(kPinPot);
  flashing = map(sensorValue, 0, 1023, 0, 255);
  digitalWrite(kPinLed, HIGH);
  delay(flashing);
  digitalWrite(kPinLed, LOW);
  delay(flashing);
}