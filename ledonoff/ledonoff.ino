const int buttonPin = 2;
const int ledPin = 13;
int ledONOFF = 0;

int buttonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if (ledONOFF == 0){
     ledONOFF = 1;
    }else{
     ledONOFF = 0;
    }
  }
  if(ledONOFF == 0) {
    digitalWrite(ledPin, LOW);
  }
  else {
    digitalWrite(ledPin, HIGH);

  }
    delay(300);
}
