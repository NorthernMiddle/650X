/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       armlift.hpp                                                 */
/*    Author:       NMS_RP                                                    */
/*    Created:      Thurs Oct 31 2019                                         */
/*    Description:  Arm Lift Function File for TT                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ArmLift              Red Motor      9                                       
// ---- END VEXCODE CONFIGURED DEVICES ----

// VEX V5 C++ Project
#include "robot-config.h"

// local variable(s)
int armSpeedPCT = 80;

/** 
  * arm lift function file
  * Pressing L1 to rise arms to pull blocks into the tray
  * Pressing L2 to lower arms to push blocks out of the tray
  * Not pressing L1 or L2 does not lift or lower arms. Arms hold in place.
  *
  **/

// arm lift function
void armLift(){
  if(con.ButtonL1.pressing()){
    ArmLift.spin( forward, armSpeedPCT, velocityUnits::pct );
  }
  else if(con.ButtonL2.pressing()){
    ArmLift.spin( reverse, armSpeedPCT, velocityUnits::pct );
  }
  else{
    ArmLift.stop( brake );
  }
}
