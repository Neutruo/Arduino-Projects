int P_LEDR = 5;
int P_LEDY = 6;
int P_LEDG = 7;
void setup() {
  pinMode(P_LEDR, OUTPUT) ;
  pinMode(P_LEDY, OUTPUT) ;  
  pinMode(P_LEDG, OUTPUT) ;
}

void loop() {
  digitalWrite(P_LEDG, HIGH);
  delay(5000);
  digitalWrite(P_LEDG, LOW);
  digitalWrite(P_LEDY, HIGH);
  delay(2000);
  digitalWrite(P_LEDY, LOW);
  digitalWrite(P_LEDR, HIGH);
  delay(5000);
  digitalWrite(P_LEDR, LOW);
}
