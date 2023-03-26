#include <pigpio.h>
#include <signal.h>

#include "Serial.h"

Serial::Serial(std::string sertty, unsigned baud) {
    m_handle = serOpen(sertty.data(), baud, 0);
}

int Serial::Write(int input) {
    return serWriteByte(m_handle, input);
}

int Serial::Write(std::string input) {
    char *buf = input.data();
    return serWrite(m_handle, buf, sizeof(input));
}