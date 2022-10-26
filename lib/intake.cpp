/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       intake.cpp                                                */
/*    Author:       NMS_RP                                                    */
/*    Created:      Thur Oct 24 2019                                          */
/*    Description:  Intake Spinners Motor Control                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

// local variables
int intakeSpeedPCT = 100; 

/** 
  * cube intake spinners function
  * Pressing L1 to run intake spinners to pull blocks into the tray
  * Pressing L2 to run intake spinners to push blocks out of the tray
  * Not pressing L1 or L2 does not run intake spinners. Intake spinners hold in place.
  *
  **/
int intake_f(){
  int count = 0;
  while(true){
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Intake has iterated %d times", count);
  count++;

    if(Controller1. ButtonL1.pressing()){
      L_Intake.spin( forward, intakeSpeedPCT, velocityUnits::pct );
      R_Intake.spin( reverse, intakeSpeedPCT, velocityUnits::pct );
    }
    else if(Controller1.ButtonL2.pressing()){
      L_Intake.spin( reverse, intakeSpeedPCT, velocityUnits::pct );
      R_Intake.spin( forward, intakeSpeedPCT, velocityUnits::pct );
      }
    else{
      L_Intake.stop( brake );
      R_Intake.stop( brake );
    }
    /* You must sleep threads by using the 'this_thread::sleep_for(unit in
    msec)' command to prevent this thread from using all of the CPU's
    resources. */
    this_thread::sleep_for( 25 );
  }

  /* A threads's callback must return an int, even though the code will never
  get here. You must return an int here. Threads can exit, but this one does not. */
  return( 0 );
}
