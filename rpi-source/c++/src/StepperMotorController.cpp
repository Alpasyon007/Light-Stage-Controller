#include "StepperMotorController.h"

#include <pigpio.h>

#include <iostream>
#include <algorithm>
#include <limits>

#define MOTOR_STEP_DELAY 0.002f

StepperMotorController::StepperMotorController(int stepPin, int dirPin, float stepDelay) : 
m_stepPinGPIO(stepPin), m_dirPinGPIO(dirPin), m_stepDelay(std::clamp(stepDelay, 0.003f, std::numeric_limits<float>::max())) {
    gpioSetMode(m_stepPinGPIO, PI_OUTPUT);
	gpioSetMode(m_dirPinGPIO, PI_OUTPUT);
};


void StepperMotorController::Step() {
	gpioWrite(m_stepPinGPIO, 1);
    time_sleep(MOTOR_STEP_DELAY);
	gpioWrite(m_stepPinGPIO, 0);
	time_sleep(m_stepDelay);
};

void StepperMotorController::StepForward(int numOfSteps) {
    gpioWrite(m_dirPinGPIO, 0);
    for(int i = 0; i < numOfSteps; i++) {
        printf("Step Forward: %d/%d with a delay of %f\n", (i + 1), numOfSteps, m_stepDelay);
        Step();
    }
};

void StepperMotorController::StepBackward(int numOfSteps) {
    gpioWrite(m_dirPinGPIO, 1);
    for(int i = 0; i < numOfSteps; i++) {
        printf("Step Backward: %d/%d with a delay of %f\n", (i + 1), numOfSteps, m_stepDelay);
        Step();
    }
};