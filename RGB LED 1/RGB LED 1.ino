int RGBLEDB = 9;
int RGBLEDG = 10;
int RGBLEDR = 11;
void setup() {
  pinMode(RGBLEDB, OUTPUT);
  pinMode(RGBLEDG, OUTPUT);
  pinMode(RGBLEDR, OUTPUT);

}
void loop() {
  digitalWrite(RGBLEDR, HIGH);
  delay(1000);
  digitalWrite(RGBLEDR, LOW);
  digitalWrite(RGBLEDG, HIGH);
  delay(1000);
  digitalWrite(RGBLEDG, LOW);
  digitalWrite(RGBLEDB, HIGH);
  delay(1000);
  digitalWrite(RGBLEDB, LOW);
}
