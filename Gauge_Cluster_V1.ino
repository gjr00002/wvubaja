#include <Adafruit_NeoPixel.h>

int PixVal = 0;
int pixCnt = 24;

int rings = 2;

Adafruit_NeoPixel pixel1(pixCnt, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel2(pixCnt, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel3(pixCnt, 3, NEO_GRB + NEO_KHZ800);

void setup() {
  if (rings == 1) {
    pixel1.begin();
  } else if (rings == 2) {
    pixel1.begin();
    pixel2.begin();
    
  } else if (rings == 3) {
    pixel1.begin();
    pixel2.begin();
    pixel3.begin();
  }

  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A0, INPUT);
}

void sensorPixel1(int sensor, int startPix, int endPix, int coR, int coG, int coB) {
  pixel1.clear();
  float reading = analogRead(sensor);
  PixVal = map(reading, 20, 1000, startPix, endPix);
  if (PixVal != 0) {
    pixel1.setBrightness(pixBrightness());
    pixel1.fill(pixel1.Color(coR, coG, coB), 0, PixVal);
  }
  pixel1.show();
}

void sensorPixel2(int sensor, int startPix, int endPix, int coR, int coG, int coB) {
  pixel2.clear();
  float reading = analogRead(sensor);
  PixVal = map(reading, 20, 1000, startPix, endPix);
  if (PixVal != 0) {
    pixel2.setBrightness(pixBrightness());
    pixel2.fill(pixel2.Color(coR, coG, coB), 0, PixVal);
  }
  pixel2.show();
}

void sensorPixel3(int sensor, int startPix, int endPix, int coR, int coG, int coB) {
  pixel3.clear();
  float reading = analogRead(sensor);
  PixVal = map(reading, 20, 1000, startPix, endPix);
  if (PixVal != 0) {
    pixel3.setBrightness(pixBrightness());
    pixel3.fill(pixel3.Color(coR, coG, coB), 0, PixVal);
  }
  pixel3.show();
}

int pixBrightness(){
  int val = analogRead(A0);
  return map(val, 0, 1023, 5, 255);
}

void loop() {
  if (rings == 1) {
    sensorPixel1(A5, 0, pixCnt, 255, 0, 0);
  } else if (rings == 2) {
    sensorPixel1(A5, 0, pixCnt, 255, 0, 0);
    sensorPixel2(A4, 0, pixCnt, 0, 255, 0);
  } else if (rings == 3) {
    sensorPixel1(A5, 0, pixCnt, 255, 0, 0);
    sensorPixel2(A4, 0, pixCnt, 0, 255, 0);
    sensorPixel3(A3, 0, pixCnt, 0, 0, 255);
  }
}
