int toggle = 0;
#define led 13
#define CLEAR 0
#define SET 1
#define ON 1
#define OFF 0

//clear = 0
unsigned char timer500ms = CLEAR ;
unsigned long lastimer = CLEAR;
unsigned char ledstatus = ON;

void setup()
{
// put your setup code here, to run once:
pinMode(led, OUTPUT);
}

void timer() 
{
    // put your main code here, to run repeatedly:
  unsigned long data;
  timer500ms = CLEAR;

  
  data = millis();
  
  if ((data-lastimer)>=500) 
  {
    timer500ms = SET;
    lastimer = millis();
  }

}

void loop() 
{

  timer();
  
  if(timer500ms == SET) 
  {
    

      toggle = !toggle;
      ledcounter = CLEAR;
      digitalWrite(led,toggle);

    
  }
}
