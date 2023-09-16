
int kPinledG = 9;
int LEDbrightness = 0;
int updown = 0;


void setup() 
{
  // put your setup code here, to run once:
  pinMode(kPinledG, OUTPUT);
}

void loop() 
{

  if(updown == 0)
  {
    
    LEDbrightness=LEDbrightness+5;
    if(LEDbrightness>255)
    {
      updown = 1;
      LEDbrightness = 255;
    }
  }
  
  else if(updown==1)
  {
    
   LEDbrightness=LEDbrightness-5;
   if(LEDbrightness<0)
   {
     updown = 0;
     LEDbrightness = 0;
   }
  }

  analogWrite( kPinledG,LEDbrightness);
  delay(100);
}