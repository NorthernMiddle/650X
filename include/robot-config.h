/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot_config.h                                            */
/*    Author:       LoJac10                                                   */
/*    Created:      Oct 30th, 2022                                            */
/*    Description:  Default header for robot_configuration file for           */
/*                   VEX Projects (aka HAL)                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor intake;
extern motor LFmotor;
extern motor LBmotor;
extern motor_group LeftSide;
extern motor RFmotor;
extern motor RBmotor;
extern motor_group RightSide;
extern drivetrain Drivetrain;
extern motor flyWheel1;
extern motor flywheel2;
extern motor_group flyWheels;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);

