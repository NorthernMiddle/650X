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

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true)
  {
    // thread for TRAY LIFT FUNCTIONS
    thread t( TLSelection_Thread);
    // Sleep the task for a short amount of time to prevent wasted resources
    wait(25, msec);
  }
}
