#pragma once

class StepperMotorController {
	public:
		StepperMotorController(int stepPin, int dirPin, float stepDelay);

        void StepForward(int numOfSteps);
        void StepBackward(int numOfSteps);

    private:
        void Step();
    public:
	private:
        int m_stepPinGPIO;
        int m_dirPinGPIO;

		float m_stepDelay;
};