/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       NMS_RP                                                    */
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

// VEX V5 C++ Project
#include "vex.h"
#include "tankDrive.h"
#include "trayLift.h"
#include "intake.h"
using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // @TODO: Place 1:45sec timer on threads
  // @TODO: At end of timer, end threads
  thread tankdrive_t = thread(tankDrive_f);     // thread DRIVE
  thread lift_t = thread(trayLift_f);           // thread TRAY LIFT
  thread spinners_t = thread(intake_f);         // thread INTAKE
}
