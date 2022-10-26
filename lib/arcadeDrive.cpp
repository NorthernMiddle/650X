/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       arcadeDrive.cpp                                           */
/*    Author:       VEX                                                       */
/*    Created:      Tue Oct 18, 2022                                          */
/*    Description:  Right Joystick Arcade Drive                               */
/*    This program allows you to control a V5 bot using the right             */
/*    joystick. Adjust the deadband value for more accurate movements.        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Con                  controller                    
// LeftMotor            motor         1               
// RightMotor           motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"

// Deadband stops the motors when Axis values are close to zero.
#define JOYSTICK_DEADZONE 8

using namespace vex;


void arcadeDrive() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // get left motor expo value
  int getLeftMotorExpoValue(int leftMotorSpeed)
  {
    int output_leftMotors = 0;
    
    // Get the velocity percentage of the left motor. (Axis2 + Axis1)
    int leftMotorSpeed = Con.Axis2.position() + Con.Axis1.position();
    
    // ignore controller value if value is too small
    if(abs(leftMotorSpeed) > JOYSTICK_DEADZONE)
      
    {
      // direction is either 1 or -1, based on controller value (cv)
      int LeftMotorDirection = abs(leftMotorSpeed) / leftMotorSpeed; 
      
      // plug controller value into exponential function
      output_leftMotors = LeftMotorDirection * (1.2 * pow(1.0356, abs(leftMotorSpeed)) - 1.2 + 0.2 * abs(leftMotorSpeed));
    }
    
    return output_leftMotors;
  }

  // get right motor expo value
  int getRightMotorExpoValue(int rightMotorSpeed)
  {
    int output_rightMotors = 0;
    
    // Get the velocity percentage of the right motor. (Axis2 - Axis1)
    int rightMotorSpeed = Con.Axis2.position() - Con.Axis1.position();
    
    // ignore controller value if value is too small
    if(abs(rightMotorSpeed) > JOYSTICK_DEADZONE)
      
    {
      // direction is either 1 or -1, based on controller value (cv)
      int RightMotorDirection = abs(rightMotorSpeed) / rightMotorSpeed; 
      
      // plug controller value into exponential function
      output_rightMotors = RightMotorDirection * (1.2 * pow(1.0356, abs(rightMotorSpeed)) - 1.2 + 0.2 * abs(rightMotorSpeed));
    }
    
    return output_rightMotors;
  }

    // the output is then used with whatever type of driver control layout (tank, arcade, etc. )
    int leftPower = getLeftMotorExpoValue(int leftMotorSpeed);
    int rightPower = getRightMotorExpoValue(int rightMotorSpeed);

    driveLeftMotors = leftPower;
    driveRightMotors = rightPower;
}

    //////////////////////////////
    //
    // Standard Right Arcarde Drive Program
    // Start Program ...
    //
    ///////////////////////////////////////////
  /*
  while (true) 
  {

    // Get the velocity percentage of the left motor. (Axis2 + Axis1)
    // Get the velocity percentage of the right motor. (Axis2 - Axis1)
    
    int leftMotorSpeed = Con.Axis2.position() + Con.Axis1.position();
    int rightMotorSpeed = Con.Axis2.position() - Con.Axis1.position();

    // Set the speed of the left motor. If the value is less than the deadband, set it to zero.
    if (abs(leftMotorSpeed) < JOYSTICK_DEADZONE) 
    {
      // Set the speed to zero.
      LeftMotor.setVelocity(0, percent);
    } 
    else 
    {
      // Set the speed to leftMotorSpeed
      LeftMotor.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband, set it to zero.
    if (abs(rightMotorSpeed) < JOYSTICK_DEADZONE) 
    {
      // Set the speed to zero
      RightMotor.setVelocity(0, percent);
    } 
    else 
    {
      // Set the speed to rightMotorSpeed
      RightMotor.setVelocity(rightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    LeftMotor.spin(forward);
    RightMotor.spin(forward);
  }
  */

    //////////////////////////////
    //
    // End Program ...
    //
    ///////////////////////////////////////////
