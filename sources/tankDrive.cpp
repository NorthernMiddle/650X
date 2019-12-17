/*----------------------------------------------------------------------------------------*/
/*                                                                                        */
/*   	Module:       tankDrive.cpp                                                        */
/*   	Author:       NMS_RP                                                               */
/*   	Created:      16 Dec 2019                                                          */
/*  	Description:  tank drive with deadband and cubic power input for VEX V5            */
/*                                                                                        */
/*----------------------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

// deadband threshold
const int deadband = 15; 

// tank drive --- variable intializations
int fwdBck_pct_left = Controller1.Axis3.position();
int fwdBck_pct_right = Controller1.Axis2.position();
double drive_lval = Controller1.Axis3.value();
double drive_rval = Controller1.Axis2.value();




/** 
  * --- Cubic Scale Factor --- 
  * Description: Functions used to achieve more sensitivity at low motor power
  *              used for precise movements while still being able to use 100% power
  *
  */
int cube_drive_lval(int drive_lval){				// tank drive cube scale factor
    return  pow(drive_lval/100.0, 3.0)*100.0;
}
int cube_drive_rval(int drive_rval){				// tank drive cube scale factor
    return  pow(drive_rval/100.0, 3.0)*100.0;
}

///////////////////////////////////////////////////////////////
//
//  --- Tank Drive with Deadband and Cubic Power Input ---
//
///////////////////////////////////////////////////////////////
/**
  * module: tank drive
  * @PARAM: Axis3 Left Side Motors
  * @PARAM: Axis2 Right Side Motors
  * @TODO:
  *
  */
int tankDrive(){
  // deadband, set to 0 if below the deadband value
  if( abs( fwdBck_pct_left  ) < deadband ) fwdBck_pct_left  = 0;
  if( abs( fwdBck_pct_right ) < deadband ) fwdBck_pct_right = 0;
 
  /* --- send to motors --- */
  // left tank motors
  LFmotor.spin( forward, cube_drive_lval, velocityUnits::pct );
  LBmotor.spin( forward, cube_drive_lval, velocityUnits::pct );
  // right tank motors
  RFmotor.spin( forward, cube_drive_rval, velocityUnits::pct );
  RBmotor.spin( forward, cube_drive_rval, velocityUnits::pct );

  // allow other tasks to run
  this_thread::sleep_for( 10 );
}
