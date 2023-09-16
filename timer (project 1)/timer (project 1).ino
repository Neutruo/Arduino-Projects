#define led 13
#define CLEAR 0
#define SET 1
#define ON 1
#define OFF 0

//clear = 0
unsigned char timer100ms = CLEAR ;
unsigned long lastimer = CLEAR;
unsigned char timer500ms = CLEAR;
unsigned char timer500cnt = CLEAR;


unsigned char ledstatus = ON;
unsigned char ledcounter = CLEAR;



void setup()
{
// put your setup code here, to run once:
pinMode(led, OUTPUT);
Serial.begin(9600);
}

void timer() 
{
    // put your main code here, to run repeatedly:
  unsigned long data;

  timer100ms = CLEAR;
  timer500ms = CLEAR;
  
  data = millis();

  Serial.println("");
  Serial.print("data: ");
  Serial.println(data);
  Serial.print("lastimer: ");
  Serial.println(lastimer);
  Serial.print("data-lastimer: ");
  Serial.println(data-lastimer);

  if ((data-lastimer)>=100) 
  {
    Serial.println("Enter loop 1");

    timer100ms = SET;

    lastimer = millis();
  }

}

void loop() 
{

  timer();
  if(timer100ms == SET) 
  {
    
    Serial.println("Enter loop 2");
    Serial.print("ledcounter:");
    Serial.println(ledcounter);
    //ledcounter++;
    if( ledcounter++> 10)
    {
      Serial.println("Enter loop 3");
      ledcounter = CLEAR;
      digitalWrite(led,ledstatus);
      if (ledstatus == OFF)
      {
        ledstatus = ON;
        Serial.print("led on");
      }

      else
      {
        ledstatus = OFF;
        Serial.print("led off");
      }
    }
  }
}
