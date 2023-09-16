
int kPinledG = 9;
int LEDbrightness = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(kPinledG, OUTPUT);
}

void loop() 
{

  if(LEDbrightness == 255) 
  {
    LEDbrightness = 0;
  }

  else
  {
    analogWrite( kPinledG,LEDbrightness);
    delay(50);
    LEDbrightness++;
  }

  
}