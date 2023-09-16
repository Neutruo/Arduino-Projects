
int kPinledG = 9;
int LEDbrightness = 255;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(kPinledG, OUTPUT);
}

void loop() 
{

  if(LEDbrightness < 0) 
  {
    LEDbrightness = 255;
  }

  else
  {
    analogWrite( kPinledG,LEDbrightness);
    delay(100);
    LEDbrightness = LEDbrightness - 15;
  }

  
}