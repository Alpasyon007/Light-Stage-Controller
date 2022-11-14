#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
#define NUMPIXELS 144

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  pixels.clear();
  
  int incomingByte = "-1"; // for incoming serial data

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    pixels.fill(pixels.Color(0, 0, 0));
    if(incomingByte != -1) {
      pixels.setPixelColor(incomingByte, pixels.Color(255, 255, 255));
    }
    pixels.show();
  }
}