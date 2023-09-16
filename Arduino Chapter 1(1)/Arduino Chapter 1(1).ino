int P_LEDY = 8;
int P_LEDR = 9;
int P_LEDB = 10;
int P_LEDG = 11;

void setup() {
  pinMode(P_LEDY, OUTPUT) ;
  pinMode(P_LEDR, OUTPUT) ;
  pinMode(P_LEDB, OUTPUT) ;
  pinMode(P_LEDG, OUTPUT) ;
}

void loop() {
  digitalWrite(P_LEDY, HIGH) ;
  digitalWrite(P_LEDB, HIGH) ;
  digitalWrite(P_LEDR, LOW) ;
  digitalWrite(P_LEDG, LOW) ;
  delay(1000) ;
  digitalWrite(P_LEDY, LOW) ;
  digitalWrite(P_LEDB, HIGH) ;
  digitalWrite(P_LEDR, HIGH) ;
  digitalWrite(P_LEDG, LOW) ;
  delay(1000) ;
  digitalWrite(P_LEDY, LOW) ;
  digitalWrite(P_LEDB, LOW) ;
  digitalWrite(P_LEDR, HIGH) ;
  digitalWrite(P_LEDG, HIGH) ;
  delay(1000) ;
  digitalWrite(P_LEDY, HIGH) ;
  digitalWrite(P_LEDB, LOW) ;
  digitalWrite(P_LEDR, LOW) ;
  digitalWrite(P_LEDG, HIGH) ;
  delay(1000) ;
}
