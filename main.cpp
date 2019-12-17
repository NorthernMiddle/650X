/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\reece.turner                                     */
/*    Created:      Fri Dec 06 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LFmotor              motor         1               
// LBmotor              motor         2               
// RFmotor              motor         3               
// RBmotor              motor         4               
// TLmotor              motor         8               
// TLlimit              limit         B               
// ---- END VEXCODE CONFIGURED DEVICES ----

/**
 * main.c - Entry point for our codebase
 * The structure of the project is as follows:
 *
 * lib/
 *   hal.c    - Hardware Abstraction Layer
 *   lcd.c    - LCD Library
 *   motor.c  - Motor Algorithmns
 *   pid.c    - General purpose PID (Super simple, basically just makes the calculation)
 *   rerun.c  - Contains code for the rerun system
 * routines/
 *   auton.c  - Routines for the 15-second autonomous
 *   skills.c - Routines for the 60-second programming skills
 *
 **/

// VEX V5 C++ Project
#include "vex.h"
#include "tankDrive.h"
#include "trayLift.h"
#include "intake.h"
using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true)
  {
    // thread DRIVE
    THREAD drive(tankDrive);
     /* sleep the task for a short amount of time to prevent wasted resources
        don't hog the CPU :-) */
    wait(25, msec);
    
    // thread TRAY LIFT
    THREAD lift(trayLift);
    /* sleep the task for a short amount of time to prevent wasted resources
       don't hog the CPU :-) */
    wait(25, msec);
    
    // thread INTAKE
   THREAD spinners(intake);
    /* sleep the task for a short amount of time to prevent wasted resources
       don't hog the CPU :-) */
    wait(25, msec);
    
  }
}
