#pragma once
#include "Serial.h"

class LEDController {
	public:
		enum LED_MODE {
			SINGLE = 1,
			QUAD = 4,
			ALL = 0,
		};

		LEDController(LED_MODE mode);

		LED_MODE GetMode() { return m_mode; }
		void SetMode(LED_MODE mode) { m_mode = mode; }

		void LightLED(int index);
	private:
		LED_MODE m_mode;
		Serial m_serial;
};