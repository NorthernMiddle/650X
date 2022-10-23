#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

motor TrayLiftCentermotor = motor(PORT9, ratio36_1, true);
//motor TrayLiftExtramotor = motor(PORT5, ratio36_1, false);
//motor_group TrayLiftmotors(TrayLiftCentermotor, TrayLiftExtramotor);

limit TrayLiftlimit = limit(Brain.ThreeWirePort.B);

motor L_Intake = motor(PORT2, ratio36_1, true);
motor R_Intake = motor(PORT10, ratio36_1, false);
motor_group Spinners(L_Intake, R_Intake);

motor LFmotor = motor(PORT3, ratio18_1, false);
motor LBmotor = motor(PORT6, ratio18_1, false);
motor STRAFmotor = motor(PORT4, ratio36_1, false);
motor_group LeftSide = motor_group(LFmotor, LBmotor);

motor RFmotor = motor(PORT8, ratio18_1, true); 
motor RBmotor = motor(PORT5, ratio18_1, true); 
motor_group RightSide = motor_group(RFmotor, RBmotor);

drivetrain Drivetrain = drivetrain(LeftSide, RightSide, 299.24, 304.79999999999995, 228.6, mm, 1);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
