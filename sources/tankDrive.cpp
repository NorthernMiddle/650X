/*----------------------------------------------------------------------------------------*/
/*                                                                                        */
/*   	Module:       tankDrive.cpp                                                        */
/*   	Author:       NMS_RP                                                               */
/*   	Created:      16 Dec 2019                                                          */
/*  	Description:  tank drive with deadband and cubic power input for VEX V5            */
/*                                                                                        */
/*----------------------------------------------------------------------------------------*/

// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

// deadband threshold
const int deadband = 15; 

// tank drive --- variable intializations
int fwdBck_pct_left = Controller1.Axis3.position();     // used for deadband monitoring
int fwdBck_pct_right = Controller1.Axis2.position();    // used for deadband monitoring
double drive_lval = Controller1.Axis3.value();          // tank drive control
double drive_rval = Controller1.Axis2.value();          // tank drive control

/** 
  * --- Cubic Scale Factor --- 
  * Description: Functions used to achieve more sensitivity at low motor power
  *              used for precise movements while still being able to use 100% power
  *
  */
int cube_drive_lval(int drive_lval){				// tank drive cube scale factor left joy
    return  pow(drive_lval/100.0, 3.0)*100.0;
}
int cube_drive_rval(int drive_rval){				// tank drive cube scale factor right joy
    return  pow(drive_rval/100.0, 3.0)*100.0;
}

/**
  * --- tankDrive callback function ---
  * func to be registered to a thread
  * func registered to 
  *
  */
int tankDrive(){
 int count = 0;
 while(true){
  Brain.Screen.setCursor(1,1);
  Brain.ScreenPrint("TankDrive has iterated %d times", count);
  count++;
  
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

  /* You must sleep threads by using the 'this_thread::sleep_for(unit in
     msec)' command to prevent this thread from using all of the CPU's
     resources. */
  this_thread::sleep_for( 25 );
}
/* A threads's callback must return an int, even though the code will never
   get here. You must return an int here. Threads can exit, but this one does not. */
return 0;
}
