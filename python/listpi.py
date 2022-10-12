# from gpiozero import Servo
# from time import sleep

# servo = Servo(24)

# try:
# 	servo.min()
# 	sleep(0.5)
# 	servo.mid()
# 	sleep(0.5)
# 	servo.max()
# 	sleep(0.5)
# except KeyboardInterrupt:
# 	print("Program stopped")

# System imports
import RPi.GPIO as GPIO
from time import sleep
import board
import neopixel

class StepperHandler():

	__CLOCKWISE = 1
	__ANTI_CLOCKWISE = 0

	def __init__(self, stepPin, directionPin, delay=0.208, stepsPerRevolution=200):
		# Configure instance
		self.CLOCKWISE = self.__CLOCKWISE
		self.ANTI_CLOCKWISE = self.__ANTI_CLOCKWISE
		self.StepPin = stepPin
		self.DirectionPin = directionPin
		self.Delay = delay
		self.RevolutionSteps = stepsPerRevolution
		self.CurrentDirection = self.CLOCKWISE
		self.CurrentStep = 0

		# Setup gpio pins
		GPIO.setmode(GPIO.BCM)
		GPIO.setwarnings(False)
		GPIO.setup(self.StepPin, GPIO.OUT)
		GPIO.setup(self.DirectionPin, GPIO.OUT)

	def Step(self, stepsToTake, direction = __CLOCKWISE):
		print("Step Pin: " + str(self.StepPin) + " Direction Pin: " + str(self.DirectionPin) + " Delay: " + str(self.Delay))
		print("Taking " + str(stepsToTake) + " steps.")

		# Set the direction
		GPIO.output(self.DirectionPin, direction)

		# Take requested number of steps
		for x in range(stepsToTake):
			print("Step " + str(x))
			GPIO.output(self.StepPin, GPIO.HIGH)
			self.CurrentStep += 1
			sleep(self.Delay)
			GPIO.output(self.StepPin, GPIO.LOW)
			sleep(self.Delay)

# Define pins
STEP_PIN = 16
DIRECTION_PIN = 21

# Create a new instance of our stepper class (note if you're just starting out with this you're probably better off using a delay of ~0.1)
stepperHandler = StepperHandler(STEP_PIN, DIRECTION_PIN, 0.0025)

# Go forwards once
stepperHandler.Step(200)

# Go backwards once
stepperHandler.Step(200, stepperHandler.ANTI_CLOCKWISE)

# pixels = neopixel.NeoPixel(board.D12, 72)
# pixels[0] = (255, 0, 0)
# pixels.fill((255, 255, 255))