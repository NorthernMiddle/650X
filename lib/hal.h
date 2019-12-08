*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       hal.h                                                     */
/*    Author:       NMS_RP                                                    */
/*    Created:      Mon 18 Nov 2019                                           */
/*    Description:  Hardware Abstraction layer, abstacts motors &             */
/*                  sensors into a set of accessor functions                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LBmotor              Green Motor    2              
// LFmotor              Green Motor    1              
// RBmotor              Green Motor    10              
// RFmotor              Green Motor    9                         
// ---- END VEXCODE CONFIGURED DEVICES ----

/*
// VEX V5 C++ Project
#include "vex.h"
#include "motor.h"
#include "util.h"
#include "pid.h"
#include "profile.h"
using namespace vex;
*/




// Section 1: Drive 
void drive(int left, int right) {
  robot.leftDrive = left;
  robot.rightDrive = right;
}



void driveReset() {                  // resetRotation(void)
  leftDrive.resetRoation();          // Resets the rotation of the left drive motor encoders to zero  
  rightDrive.resetRoation();         // Resets the rotation of the right drive motor encoders to zero       
}

int driveOffset() {
  // return SensorValue[leftDrive] - SensorValue[rightDrive];
  return leftDrive.encoder.rotation() - rightDrive.encoder.rotion();  
}

/*
void driveHandle() {
    motorTarget[port4] = -robot.leftDrive;
    motorTarget[port6] = -robot.leftDrive;
    motorTarget[port8] = -robot.leftDrive;

    motorTarget[port5] = robot.rightDrive;
    motorTarget[port7] = robot.rightDrive;
    motorTarget[port9] = robot.rightDrive;
}
*/

/**
  * Drives a set number of specified inches
  */
 /*
pidConfiguration drivePID;
void driveDistance(int inches) {
    pidConfigure(drivePID, 0, 0, 0);
    pidReset(drivePID);

    int targetTicks = inchesToTicks(inches, 3.25, 3, TORQUE);

    while(SensorValue[leftDrive] != targetTicks || SensorValue[rightDrive] != targetTicks) {
        int syncspeed = pidCalculate(drivePID, driveOffset()),
            basespeed = 90 * profileTrapezoid(targetTicks, SensorValue[leftDrive], 1/8); 
        drive(basespeed - syncspeed, basespeed + syncspeed);
    }

    // Stop the drive after we've completed the distance
    drive(0, 0);
}
*/

// Section 2: tray Lift 
/*
void traySet(int value) {
    motorTarget[port8] = value;
}

void mogoHandle() {
    if(robot.mogo == UP && SensorValue[mogoLeft] > 150) {
        mogoSet(100);
    } else if (robot.mogo == DOWN && SensorValue[mogoLeft] < 2400) {
        mogoSet(-100);
    } else {
        mogoSet(0);
    }
}

void mogoUp() {
    robot.mogo = UP;
}
void mogoDown() {
    robot.mogo = DOWN;
}


task handleAll() {
    while(true) {
        mogoHandle();
        driveHandle();
        motorHandle();
        wait1Msec(20);
    }
}
*/
