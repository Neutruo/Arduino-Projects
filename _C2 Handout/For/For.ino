const int P_LEDR = 3;
int delayTime=1000;
void setup()
 {
  pinMode(P_LEDR, OUTPUT);
 }

void loop()
{
  for(int i = 0; i <127; i++){
   analogWrite(P_LEDR, i);
   delay(50);
  }
  for(int i = 127; i >0; i--){
   analogWrite(P_LEDR, i);
   delay(50);
  }
  delay(delayTime); // 1 second
}  









