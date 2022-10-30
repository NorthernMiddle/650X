#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

///////////////////////////////////
//
// VEXcode device constructors
//
/////////////////////////////////////////////////////////

// controller
controller Controller1 = controller(primary);

// flywheel
motor flyWheel1 = motor(PORT8, ratio18_1, true); 
motor flyWheel2 = motor(PORT5, ratio18_1, false); 
motor_group flyWheels = motor_group(flyWheel1, flyWheel2);

// intake
motor intake = motor(PORT2, ratio36_1, false);

// motors & drivetrain
motor LFmotor = motor(PORT3, ratio18_1, false);
motor LBmotor = motor(PORT6, ratio18_1, false);
motor_group LeftSide = motor_group(LFmotor, LBmotor);

motor RFmotor = motor(PORT8, ratio18_1, true); 
motor RBmotor = motor(PORT5, ratio18_1, true); 
motor_group RightSide = motor_group(RFmotor, RBmotor);

smartdrive Drivetrain = smartdrive(LeftSide, RightSide, TurnGyroSmart, 319.19, 320, 130, mm, 1);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

///////////////////////////////////
//
// VEXcode Initialization
//
/////////////////////////////////////////////////////////

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  
  // start initialization
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.startCalibration(1);
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}
