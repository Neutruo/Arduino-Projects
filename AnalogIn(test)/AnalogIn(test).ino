const int kPinPot = A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(kPinPot, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue=0;
  sensorValue=analogRead(kPinPot);
  Serial.println(sensorValue);
}
