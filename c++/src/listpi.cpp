#include <pigpio.h>
#include <signal.h>

#include <iostream>

int main() {
	if (gpioInitialise() < 0) return -1;
	std::cout << "Initalised GPIO" << std::endl;

	int servo = 24;

	std::cout << "Sending servos pulses to GPIO" << std::endl;
	while(true) {
		gpioServo(servo, 500);
		time_sleep(0.1);
	}

	gpioServo(servo, 0);

	gpioTerminate();
}