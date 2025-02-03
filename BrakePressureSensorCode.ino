#include <Adafruit_NeoPixel.h>


const int sensorPin=A1;
float vout=0.0;
float vin=0.0;
float pressure=0.0;

#define PIN_NEO_PIXEL 4
#define NUM_PIXELS 1

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL), NEO_GRB + NEO_KHZ800);

void setup() {
  NeoPixel.begin();
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  

}

void loop() {
  //pinMode(6, OUTPUT);
  //digitalWrite(6, HIGH);
  NeoPixel.setPixelColor(pixel, NeoPixel.Color(255,0,0));
  NeoPixel.setBrightness(100);
  measurePressure();
  delay(250);
}
void measurePressure() {
  int voltage = analogRead(sensorPin);
  vin=(voltage)*(5/1023);
  pressure=vin*(2500/5);

  Serial.print(pressure);

}

