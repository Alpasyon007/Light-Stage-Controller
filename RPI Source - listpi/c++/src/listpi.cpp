#include <pigpio.h>
#include <signal.h>

#include <iostream>

#include "StepperMotorController.h"
#include "Serial.h"

int main() {
	if (gpioInitialise() < 0) return -1;
	Serial serial("/dev/ttyUSB0", 9600);
	// std::cout << "Initalised GPIO" << std::endl;

	// StepperMotorController stepperMotor(16, 21, 0.003f);
	// stepperMotor.StepForward(200); // 360 Degrees

	// time_sleep(1);

	// for(int i = 0; i < 10; i++) {
	// 	stepperMotor.StepForward(20);
	// 	time_sleep(1);
	// }
	
	// gpioWrite(21, 0);

	while(true) {
		serial.Write(0);
		time_sleep(1);

		for(int i = 0; i < 144; i++) {
			serial.Write(i);
			time_sleep(1);
		}
	}

	gpioTerminate();
}