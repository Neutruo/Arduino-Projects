const int kPinButton1 = 2;
const int kPinButton2 = 3;
const int kPinLed = 9;
int incomingbyte = 0;
void setup() {
  pinMode(kPinButton1, INPUT);
  pinMode(kPinButton2, INPUT);
  pinMode(kPinLed, OUTPUT);
  digitalWrite(kPinButton1, HIGH);
  digitalWrite(kPinButton2, HIGH);
  Serial.begin(9600);
}

int ledBrightness = 128;
void loop() {
  if(digitalRead(kPinButton1) == LOW){
    ledBrightness--;
  }
  else if(digitalRead(kPinButton2) == LOW){
    ledBrightness++;
  }
  Serial.print("before=");
  Serial.println(ledBrightness);
  ledBrightness = constrain(ledBrightness, 0, 255);
  Serial.print("after=");
  Serial.println(ledBrightness);
  analogWrite(kPinLed, ledBrightness);
  delay(20);
}
