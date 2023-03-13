const int sensorPin = A1;  // pin that the sensor is attached to
int sensorValue = 0;   // the sensor value
int sensorMin = 1023;  // minimum sensor value
int sensorMax = 0;     // maximum sensor value
#include <Adafruit_NeoPixel.h>
 
#define PIN      1
#define N_LEDS 2
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  calibrate();
 
}
 
void loop() {
  push();
//  party();
//  delay(100);
}
 
void calibrate() {
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
}
void push() {
  sensorValue = analogRead(sensorPin);
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  strip.setPixelColor(0, strip.Color(0, 0, sensorValue)); // Draw new pixel
 strip.show();
}
void party() {
  sensorValue = analogRead(sensorPin);
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  if (sensorValue > 100) {
    int makeRandom = int(random(3));
    if (makeRandom == 0) {
      strip.setPixelColor(0, strip.Color(255, 255, 0)); // Draw new pixel
    }else if (makeRandom == 1) {
      strip.setPixelColor(0, strip.Color(255, 0, 255)); // Draw new pixel
    } else if (makeRandom == 2) {
      strip.setPixelColor(0, strip.Color(0, 255, 255)); // Draw new pixel
    }
      strip.show();
    } else {
      strip.setPixelColor(0, strip.Color(0, 0, 0)); // Draw new pixel
      strip.show();
    }
 
  }