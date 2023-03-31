x #include <Stepper.h> 

const int stepsPerRevolution = 2038; // Defines the number of steps per rotation

Stepper stepper1 = Stepper(stepsPerRevolution, 34, 32, 35, 33); // IN1-IN3-IN2-IN4

void setup() 
{

}

void loop() 
{
	// Rotate CW slowly at 5 RPM
	stepper1.setSpeed(20);
	stepper1.step(stepsPerRevolution);
	delay(1000);
	
	// Rotate CCW quickly at 10 RPM
	stepper1.setSpeed(20);
	stepper1.step(-stepsPerRevolution);
	delay(1000);
}