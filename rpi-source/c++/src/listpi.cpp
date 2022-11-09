// pigpio
#include <pigpio.h>
#include <signal.h>

// std
#include <iostream>

// Helpers
#include "StepperMotorController.h"
#include "Serial.h"

#define MOTOR_STEP_PIN 16
#define MOTOR_DIRECTION_PIN 21
#define MOTOR_STEP_DELAY_PIN 0.003f

int main() {
	if (gpioInitialise() < 0) return -1;

	Serial serial("/dev/ttyAMA0", 9600);
	std::cout << "Initalised GPIO" << std::endl;
	StepperMotorController stepperMotor(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN, MOTOR_STEP_DELAY_PIN);

	while(true) {
		stepperMotor.StepForward(200); // 360 Degrees
		time_sleep(1);

		for(int i = 0; i < 10; i++) {
			stepperMotor.StepForward(20);
			time_sleep(1);

			serial.Write(0);
			time_sleep(1);

			for(int i = 0; i < 144; i++) {
				serial.Write(i);
				time_sleep(1);
			}
		}
	}

	gpioWrite(21, 0);
	gpioTerminate();
}