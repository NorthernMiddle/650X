/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       intakeMotors.h                                            */
/*    Author:       NMS_RP                                                    */
/*    Created:      Thur Oct 24 2019                                          */
/*    Description:  Intake Spinners Motor Control                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L_Intake             Green Motor   1               
// R_Intake             Green Motor   10                                   
// ---- END VEXCODE CONFIGURED DEVICES ----

// VEX V5 C++ Project
#include "vex.h"

// local variables
int intakeSpeedPCT = 100; 

/** 
  * cube intake spinners function
  * Pressing L1 to run intake spinners to pull blocks into the tray
  * Pressing L2 to run intake spinners to push blocks out of the tray
  * Not pressing L1 or L2 does not run intake spinners. Intake spinners hold in place.
  *
  **/
void intakeFunc(){
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
}
