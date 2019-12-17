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

// tank drive func --- variable intializations
int fwdBck_pct_left = Controller1.Axis3.position();     // used for deadband monitoring
int fwdBck_pct_right = Controller1.Axis2.position();    // used for deadband monitoring
double drive_lval = Controller1.Axis3.value();          // tank drive control
double drive_rval = Controller1.Axis2.value();          // tank drive control


// type conversions funcs and call
int input_lval(double drive_lval){
  return ceil(drive_lval);
}
int input_rval(double drive_rval){
  return ceil(drive_rval);
}

int arg1 = input_lval(drive_lval);
int arg2 = input_rval(drive_rval);


/** 
  * --- Cubic Scale Factor --- 
  * Description: Functions used to achieve more sensitivity at low motor power
  *              used for precise movements while still being able to use 100% power
  *
  */
int cube_drive_lval(int arg1){				// tank drive cube scale factor left joy
    return  pow(arg1/100.0, 3.0)*100.0;
}
int cube_drive_rval( int arg2 ){				// tank drive cube scale factor right joy
    return  pow(arg2/100.0, 3.0)*100.0;
}

double arg3 = (1.0 *(cube_drive_lval(arg1)));
double arg4 = (1.0 * (cube_drive_rval(arg2)));



/**
  * --- tankDrive_f is a callback function ---
  * func to be registered to a thread
  * func registered to thread tankdrive_t
  *
  */
int tankDrive_f(){
 int count = 0;
 while(true){
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("TankDrive has iterated %d times", count);
  count++;
  
  // deadband, set to 0 if below the deadband value
  if( abs( fwdBck_pct_left  ) < deadband ) fwdBck_pct_left  = 0;
  if( abs( fwdBck_pct_right ) < deadband ) fwdBck_pct_right = 0;
 
  /* --- send to motors --- */
  // left tank motors
  LFmotor.spin( directionType::fwd, arg3, velocityUnits::pct );
  LBmotor.spin( directionType::fwd, arg3, velocityUnits::pct );
  // right tank motors
  RFmotor.spin( directionType::fwd, arg4, velocityUnits::pct );
  RBmotor.spin( directionType::fwd, arg4, velocityUnits::pct );

  /* You must sleep threads by using the 'this_thread::sleep_for(unit in
     msec)' command to prevent this thread from using all of the CPU's
     resources. */
  this_thread::sleep_for( 25 );
}
/* A threads's callback must return an int, even though the code will never
   get here. You must return an int here. Threads can exit, but this one does not. */
return 0;
}
