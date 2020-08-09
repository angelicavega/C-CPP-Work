//This code is directly from Philipp Schrader & Tom Brown's work on Programming FRC Robots using C++
#include "WPILib.h"
class RobotDemo : public SimpleRobot
{
public:
   RobotDemo(void) { }
   void Autonomous(void) { }
   void OperatorControl(void) { }
};
START_ROBOT_CLASS(RobotDemo);

// Declare drive components
Joystick *stick;
Victor *leftDrive;
Victor *rightDrive;
// Initialize components with port numbers
RobotDemo(void) {
stick = new Joystick(1); leftDrive = new Victor(1); rightDrive = new Victor(2);
}

void OperatorControl(void) {
   while (IsOperatorControl()) {
float leftY = stick->GetRawAxis(2); float rightY = stick->GetRawAxis(4);
// Tank drive
leftDrive->SetSpeed(-leftY); rightDrive->SetSpeed(rightY);
Wait(0.005); }
}

AnalogChannel *plowPot;
RobotDemo(void) {
plowPot = new AnalogChannel(2);

}

void OperatorControl(void) {
	while (IsOperatorControl()) {
		printf("%d", plowPot -> GetValue());
		wait(0.005);
	}
}

Relay *leftPlow;
Relay *rightPlow;
RobotDemo(void) {
leftPlow = new Relay(1); rightPlow = new Relay(2);
}
void SetPlow(Relay::Value direction) { leftPlow->Set(direction); rightPlow->Set(direction);
}
void OperatorControl(void) {
   while (IsOperatorControl()) {
if (stick->GetRawButton(2)) { SetPlow(Relay::kForward);
}
else if (stick->GetRawButton(3)) {
         SetPlow(Relay::kReverse);
      }
      else {
         SetPlow(Relay::kOff);
} }
}

// Prevents the plow from going too far
if (stick->GetRawButton(2) && (plowPot->GetValue() > 60)) {
   SetPlow(Relay::kForward);
First Steps
What is programming?
Source Control
Windriver
WPILib }
Examples
Simple Robot Drive with Joystick Sensors
Simple Feedback Pneumatics Autonomous
Contact Information
else if (stick->GetRawButton(3) && (plowPot->GetValue() < 250)) {
   SetPlow(Relay::kReverse);
}
else {
   SetPlow(Relay::kOff);
}
Solenoid *openGate;
Solenoid *closeGate;
Compressor *compressor;
RobotDemo(void) {
openGate = new Solenoid(1); closeGate = new Solenoid(2); compressor = new Compressor (9, 5);
}
void OperatorControl(void) { openGate->Set(false); closeGate->Set(true);
while (IsOperatorControl()) {
if (stick->GetRawButton(1)) {
openGate->Set(true);
closeGate->Set(false); }
else if (stick->GetRawButton(4)) { openGate->Set(false); closeGate->Set(true);
}

        // Only runs compressor until 120 psi
if (!compressor->GetPressureSwitchValue()) { compressor->Start();
} else {
compressor->Stop(); }
Wait(0.005); }
}
void Autonomous(void) { int state = 1;
   while (IsAutonomous()) {
      switch (state) {
         case 1:
            if (SetPlow(Relay::kForward)) {
state = 2; }
break;
 case 2:
            if (SetPlow(Relay::kReverse)) {
case = 1;
break; 
		}
	} 
}

bool SetPlow(Relay::Value direction) { if ((direction == Relay::kForward &&
plowPot->GetValue() > 60) || (direction == Relay::kReverse &&
plowPot->GetValue() < 260)) { leftPlow->Set(direction); rightPlow->Set(direction); return false;
}
leftPlow->Set(Relay::kOff); rightPlow->Set(Relay::kOff); return true;
		}
