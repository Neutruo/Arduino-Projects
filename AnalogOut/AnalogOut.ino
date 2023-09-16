int P_LEDR = 3;
void setup() {
  pinMode(P_LEDR, OUTPUT) ;

}

void loop() {
  analogWrite(P_LEDR, 20);
  delay(100);
  analogWrite(P_LEDR, 0);
  delay(100);
}
