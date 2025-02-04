#include <LiquidCrystal_I2C.h>
#define DISPLAY_W 16

LiquidCrystal_I2C lcd(0x27,DISPLAY_W,2);

float pressure;

float revolutions=0;

const int buttonPin = A1;
bool timerRunning = true;
int minutes = 2;
int seconds = 0;
bool buttonState = false;

void setup() {
  pinMode(A0, INPUT_PULLUP);           // set pin to input
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Pressure :"); 

  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void resetTimer() {
  seconds = 3600;
  lcd.clear();
}

void updateDisplay() {
  lcd.setCursor(0, 1);
  if (seconds>=0 ) {
    lcd.print("Time Left: ");
    
    lcd.print(seconds);
    lcd.print("     ");
  } if(seconds <0 ){
    lcd.print("Time for Refuel");
    return;
  }
  seconds--;
  delay(1000);
}

void loop() {

   buttonState = digitalRead(buttonPin);
  
  if(buttonState == LOW){
    resetTimer();
  }else{
    updateDisplay();
  }

//attachInterrupt(digitalPinToInterrupt(2),interruptFunction,RISING);
//delay(1000);
//detachInterrupt(2); 

  pressure = (analogRead(A0) * 2500.0 / 2560)-109; //convert A/D reading directly to pressure
  Serial.print(pressure, 1);
  Serial.println(" PSI");
  delay(250);

  lcd.setCursor(0,0);
String outMsg = String("Pressure:") + pressure;
fillMessage2DisplayWidth(outMsg);
lcd.print(outMsg);
Serial.println(outMsg);

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