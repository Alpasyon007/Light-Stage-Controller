#include <pigpio.h>
#include <signal.h>

#include "Serial.h"

Serial::Serial(std::string sertty, unsigned baud) {
    m_handle = serOpen(sertty.data(), baud, 0);
}

int Serial::WriteByte(int input) {
	return serWriteByte(m_handle, input);
}

void Serial::WriteWord(int input) {
	serWriteByte(m_handle, input & 0xFF);
	serWriteByte(m_handle, (input >> 8) & 0xFF);
}

int Serial::Write(std::string input) {
    char *buf = input.data();
    return serWrite(m_handle, buf, sizeof(input));
}