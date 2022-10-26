#include "vex.h"
using namespace vex;

///////////////////////////////////////////////////////////////////
//
// Set Motor Functions
//  - this sets motors between -12000 and 12000.  i'm used to
//  - -100 to 100, so the "scale" variable lets me use that as
//  - inputs and scales it to -12000 to 12000
//
///////////////////////////////////////////////////////////////////

// Set voltage <-- power setting for drive
const int SCALE = 120;
void set_tank(int l, int r) {
  LeftFront.spin(fwd, l * SCALE, voltageUnits::mV);
  LeftBack.spin(fwd, l * SCALE, voltageUnits::mV);
  RightFront.spin(fwd, r * SCALE, voltageUnits::mV);
  RightBack.spin(fwd, r * SCALE, voltageUnits::mV);
  
  void set_intake(int input) {
  Intake.spin(fwd, input * SCALE, voltageUnits::mV);
}

void set_indexer(int pos, int speed) {
  Indexer.startRotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct);
}

void set_flywheel(int input) {
  Flywheel.spin(fwd, input * SCALE, voltageUnits::mV);
  Flywheel2.spin(fwd, input * SCALE, voltageUnits::mV);
}
  
//////////
//
// exponential drive function
//
////////////////////////////////////
  
 #define JOYSTICK_DEADZONE 8

int getExpoValue(int joystickValue)
{
    int output = 0;
    // Ignore joystick input if it's too small
    if(abs(joystickValue) > JOYSTICK_DEADZONE){
      // Direction is either 1 or -1, based on joystick value
      int direction = abs(joystickValue) / joystickValue;
      // Plug joystick value into exponential function
      output = direction * (1.2 * pow(1.0356, abs(joystickValue)) - 1.2 + 0.2 * abs(joystickValue));
    }
    return output;
} 

// The output is then used with whatever type of driver control layout (tank, arcade, etc.) you prefer
// A quick example of tank drive in opControl:

// Get joystick values
int leftPower = getExpoValue(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
int rightPower = getExpoValue(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
driveLeftMotor = leftPower;
driveRightMotor = rightPower;  
