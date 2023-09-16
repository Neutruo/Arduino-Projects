int toggle = 0;
#define led 13
#define CLEAR 0
#define SET 1
#define ON 1
#define OFF 0

//clear = 0
unsigned char timer100ms = CLEAR ;
unsigned long lastimer = CLEAR;
unsigned char ledstatus = ON;
unsigned char ledcounter = CLEAR;



void setup()
{
// put your setup code here, to run once:
pinMode(led, OUTPUT);
}

void timer() 
{
    // put your main code here, to run repeatedly:
  unsigned long data;
  timer100ms = CLEAR;

  
  data = millis();
  
  if ((data-lastimer)>=100) 
  {
    timer100ms = SET;
    lastimer = millis();
  }

}

void loop() 
{

  timer();
  
  if(timer100ms == SET) 
  {
    
    if( ledcounter++>5)
    {
      toggle = !toggle;
      ledcounter = CLEAR;
      digitalWrite(led,toggle);
      
      
        

      

     
      
        
 
      
    }
  }
}
