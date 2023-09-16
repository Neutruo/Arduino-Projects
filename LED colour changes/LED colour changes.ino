int RGBLEDR = 9;
int RGBLEDG = 10;
int RGBLEDB = 11;
int kPinButton = 2;

void setup() {
  pinMode(RGBLEDR, OUTPUT);
  pinMode(RGBLEDG, OUTPUT);
  pinMode(RGBLEDB, OUTPUT);
  pinMode(kPinButton, INPUT);
}
int colour = 0;
void loop() {
  if(digitalRead(kPinButton) == HIGH) {
    colour++;
    delay(300);
  }
  if(colour == 0) {
    digitalWrite(RGBLEDR, LOW);
    digitalWrite(RGBLEDG, LOW);
    digitalWrite(RGBLEDB, LOW);
  }
  if(colour == 1) {
    digitalWrite(RGBLEDR, HIGH);
    digitalWrite(RGBLEDG, LOW);
    digitalWrite(RGBLEDB, LOW);
  }
  if(colour == 2) {
    digitalWrite(RGBLEDR, LOW);
    digitalWrite(RGBLEDG, HIGH);
    digitalWrite(RGBLEDB, LOW);
  }
  if(colour == 3) {
    digitalWrite(RGBLEDR, LOW);
    digitalWrite(RGBLEDG, LOW);
    digitalWrite(RGBLEDB, HIGH);
  }
  if(colour > 3) {
    colour=1;
  }

}
