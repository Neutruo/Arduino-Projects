const int kPinLed = 2;
const int kPin
void setup() {
for(int i = 0; i < k_numberLEDs; i++) {
  pinMode(kPinLeds[i],OUTPUT);
  }
}

void loop() {
  for(int i = 0; i < k_numberLEDs; i++) {
    digitalWrite(kPinLeds[i],HIGH);
    delay(200);
    digitalWrite(kPinLeds[i],LOW);
  }
  for(int i = k_numberLEDs; i > 0; i--) {
    digitalWrite(kPinLeds[i],HIGH);
    delay(200);
    digitalWrite(kPinLeds[i],LOW);
  }
}
