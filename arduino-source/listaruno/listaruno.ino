#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
	#include <avr/power.h>
#endif
#define PIN 6
#define NUMPIXELS 144

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

int incomingByte = -1; // for incoming serial data

enum LED_MODE {
	SINGLE = 1,
	QUAD = 4,
	ALL = 0,
};

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
	clock_prescale_set(clock_div_1);
#endif

	pixels.begin();
	Serial.begin(9600);
}

void WaitForSerial() {
	while(!Serial.available()) {};
}

void loop() {
	pixels.clear();

	if (Serial.available() > 0) {
		// read the incoming byte:
		incomingByte = Serial.read();
		Serial.print("Mode: ");
		Serial.println(incomingByte);

		switch (incomingByte) {
			case LED_MODE::SINGLE: {
					incomingByte = Serial.read();
					Serial.print("LED: ");
					Serial.println(incomingByte);
					pixels.fill(pixels.Color(0, 0, 0));
					if(incomingByte != -1) {
						pixels.setPixelColor(incomingByte, pixels.Color(255, 255, 255));
					}
					pixels.show();
				}; break;
			case LED_MODE::QUAD: {
					WaitForSerial();
					incomingByte = Serial.read();
					Serial.print("LED: ");
					Serial.println(incomingByte);
					pixels.fill(pixels.Color(0, 0, 0));
					if(incomingByte != -1) {
						pixels.setPixelColor(incomingByte, pixels.Color(255, 255, 255));
						pixels.setPixelColor(incomingByte + 1, pixels.Color(255, 255, 255));
						pixels.setPixelColor(incomingByte + 2, pixels.Color(255, 255, 255));
						pixels.setPixelColor(incomingByte + 3, pixels.Color(255, 255, 255));
					}
					pixels.show();
				}; break;
			case LED_MODE::ALL:
				break;
			default:
				break;
		}
	}
}