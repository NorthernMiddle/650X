/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot_config.h                                            */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for robot_configuration file for           */
/*                   VEX Projects (aka HAL)                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor TrayLiftCentermotor;
extern motor TrayLiftExtramotor;
extern motor_group TrayLiftmotors;
extern limit TrayLiftlimit;
extern motor L_Intake;
extern motor R_Intake;
extern motor_group Spinners;
extern drivetrain Drivetrain;
extern motor STRAFmotor;
extern motor_group LeftSide;
extern motor_group RightSide;
extern motor LFmotor;
extern motor LBmotor;
extern motor RFmotor;
extern motor RBmotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);

#endif // ROBOT_CONFIG_H
