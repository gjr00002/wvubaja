#include <LiquidCrystal_I2C.h>
#define DISPLAY_W 16

LiquidCrystal_I2C lcd(0x27,DISPLAY_W,2);


float pressure;
float revolutions=0;
int rpm=0; // max value 32,767 16 bit
long  startTime=0;
long  elapsedTime;

void setup() {
  pinMode(A0, INPUT_PULLUP); 
  pinMode(2, INPUT_PULLUP);           // set pin to input
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0,0);
    //lcd.print("Pressure :"); 
    
  Serial.begin(9600);
}

void loop() {
 revolutions=0; rpm=0;
startTime=millis();         
attachInterrupt(digitalPinToInterrupt(2),interruptFunction,RISING);
delay(1000);
detachInterrupt(2);
/*
if(revolutions>0)
{
  rpm=(max(1, revolutions) * 60000) / elapsedTime;        //calculates rpm
}
*/


  pressure = (analogRead(A0) * 2500.0 / 2560) -25 ; //convert A/D reading directly to pressure
  Serial.print(pressure, 1);
  Serial.println(" PSI");
  delay(250);

  lcd.setCursor(0,0);
String outMsg = String("Pressure:") + pressure;
fillMessage2DisplayWidth(outMsg);
lcd.print(outMsg);
Serial.println(outMsg);

/*
lcd.setCursor(0,2);
String outMsg0 = String("RPM :") + rpm;
fillMessage2DisplayWidth(outMsg0);
lcd.print(outMsg0);
Serial.println(outMsg0);
*/
}
void interruptFunction() //interrupt service routine
{  
  revolutions++;
}

void fillMessage2DisplayWidth(String & message)
{
  if(message.length()<DISPLAY_W+1)
  {
    while(message.length()<DISPLAY_W)
    {
      message+=" "; 
    }
     return;
  }
   //message is too wide for 1 line of the display, truncate it
    message = message.substring(0, DISPLAY_W-1); 
}

