int RGBLEDB = 11;
int RGBLEDG = 10;
int RGBLEDR = 9;
void setup() {
  pinMode(RGBLEDR, OUTPUT);
  pinMode(RGBLEDG, OUTPUT);
  pinMode(RGBLEDB, OUTPUT);
}
void loop() {
  analogWrite(RGBLEDG, 50);
  analogWrite(RGBLEDB, 10);
  delay(2000);
  digitalWrite(RGBLEDG, LOW);
  digitalWrite(RGBLEDB, LOW);
  delay(2000);
}
