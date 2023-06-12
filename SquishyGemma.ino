// Squishy Gemma 
/* 
Lee Wilkins 2023 for Soft and Squishy Sensors workshop with Alex Bachmeyer at the Milieux Institute 

This code is useful for testing your DIY variable resistor. Your circuit 
should have a sensor connected to A1 and a NeoPixel connected to D1. You 
may need to use either a pulldown resistor, or INPUT_PULLDOWN depending on
the microcontroller you are using. 

This code has 3 functions: 
- callibrate() A callibrate function that runs on setup. This takes the max and min values 
of your sensor for the first 5 seconds. Its helpful to push down on your sensor
as soon as you start your program so it gets the widest range of values. 

- push() and party() are neopixel patterns. Push reflects the preasure with which 
you are pressing the snesor and Party selects a random color (independant of how
stronly the sensor is pressed).
*/

const int sensorPin = A1;  // pin that the sensor is attached to
int sensorValue = 0;   // the sensor value
int sensorMin = 1023;  // minimum sensor value
int sensorMax = 0;     // maximum sensor value
#include <Adafruit_NeoPixel.h> // Include the LED library
 
#define PIN 1 // NeoPixel pin
#define N_LEDS 1 // How many LEDs
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  calibrate(); // Run the callibrate function for 5 seconds when it starts
}
 
void loop() {
  push(); // Uncomment push or Party for different effects
//  party();
}
 
void calibrate() {
  /* 
  Take the readings of the sensor for 5 seconds, while the
  timer is less than 5000. Read the value, and if it is 
  greater than the max, make it the new max value. If it is
  less than the min, make it the new min value. These values are
  stored as global variables. 
  */
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
  /*
  When the sensor is pressed, take a reading of the sensor 
  value and constrains it to the max or min. Then maps the 
  value to be between 0 and 255 so that we can use the full range
  of the LED brightness. The LED will be more bright if the sensor
  is pushed harder!
  */
  sensorValue = analogRead(sensorPin);
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  strip.setPixelColor(0, strip.Color(0, 0, sensorValue)); // Draw new pixel
  strip.show();
}
void party() {
  /*
  Party selects a random color for the sensor as it is pressed. 
  */
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