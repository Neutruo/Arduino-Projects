const int kPinPot = A0;
const int kPinLed = 9;
int ledBrightness = 0;
int sensorValue = 0;
void setup() {
  pinMode(kPinPot, INPUT);
  pinMode(kPinLed, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  sensorValue = analogRead(kPinPot);
  Serial.print("sensorValue: ");
  Serial.println(sensorValue);
  ledBrightness = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(kPinLed, ledBrightness);
  Serial.print("ledBrightness: ");
  Serial.println(ledBrightness);
}
