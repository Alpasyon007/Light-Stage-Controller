#include "LEDController.h"

LEDController::LEDController(LED_MODE mode) : m_mode(mode), m_serial("/dev/ttyUSB0", 9600) {}

void LEDController::LightLED(int index) {
	m_serial.Write(m_mode);
	m_serial.Write(index);
}