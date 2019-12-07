/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       drive.h                                                   */
/*    Author:       NMS_RP                                                    */
/*    Created:      03 Dec 2019                                               */
/*    Description:  tank and arcade drive (left & right joystick options)     */
/*                  for VEX V5 with deadband                                  */
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

// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

// #region config_globals
controller Controller1 = controller( controllerType::primary );

// deadband threshold
const int deadband = 15; 

// tank drive variable declarations with intialization
int fwdBck_pct_left = Controller1.Axis3.position();
int fwdBck_pct_right = Controller1.Axis2.position();
double drive_lval = Controller1.Axis3.value();
double drive_rval = Controller1.Axis2.value();

// arcade drive variable declarations with intialization

/* --- LEFT JOYSTICK --- */
int forward_pct_leftjoy = Controller1.Axis3.position();
int turn_pct_leftjoy = Controller1.Axis4.position();
double drive_l_leftjoy = forward_pct_leftjoy + turn_pct_leftjoy;   // left '+'
double drive_r_leftjoy = forward_pct_leftjoy - turn_pct_leftjoy;   // right '-'

/* --- RIGHT JOYSTICK --- */
int forward_pct_rightjoy = Controller1.Axis2.position();
int turn_pct_rightjoy = Controller1.Axis1.position();
double drive_l_rightjoy = forward_pct_rightjoy + turn_pct_rightjoy;   // left '+'
double drive_r_rightjoy = forward_pct_rightjoy - turn_pct_rightjoy;   // right '-'


//////////////////////////////////////////////////////////
//
//  --- Tank Drive Functions with Deadband ---
//
//////////////////////////////////////////////////////////

/**
  * module: tank drive
  * @PARAM: Axis3 Left Side Motors
  * @PARAM: Axis2 Right Side Motors
  * @TODO:
  *
  */
void tankDrive(){

  // deadband, set to 0 if below the deadband value
  if( abs( fwdBck_pct_left  ) < deadband ) fwdBck_pct_left  = 0;
  if( abs( fwdBck_pct_right ) < deadband ) fwdBck_pct_right = 0;

  // send to motors
  // left tank motors
  LFmotor.spin( forward, drive_lval, velocityUnits::pct );
  LBmotor.spin( forward, drive_lval, velocityUnits::pct );
  // right tank motors
  RFmotor.spin( forward, drive_rval, velocityUnits::pct );
  RBmotor.spin( forward, drive_rval, velocityUnits::pct );

  // allow other tasks to run
  this_thread::sleep_for( 10 );

}

//////////////////////////////////////////////////////////
//
//  --- Arcade Drive Functions with Deadband ---
//
/////////////////////////////////////////////////////////

/**
  * module: ARCADE DRIVE: LEFT JOYSTICK
  * @PARAM: Left Side   ( Axis3 + Axis4 )
  * @PARAM: Right Side  ( Axis3 - Axis4 )
  * @TODO:
  *
  */
void arcadeDrive_leftJoy(){

  // DEADBAND, set to 0 if below the deadband threshold
  if( abs( forward_pct_leftjoy ) < deadband ) forward_pct_leftjoy = 0;
  if( abs( turn_pct_leftjoy    ) < deadband ) turn_pct_leftjoy = 0;

  // send to motors
  // left arcade motors
  LFmotor.spin( forward, drive_l_leftjoy, velocityUnits::pct );
  LBmotor.spin( forward, drive_l_leftjoy, velocityUnits::pct );
  // right arcade motors
  RFmotor.spin( forward, drive_r_leftjoy, velocityUnits::pct );
  RBmotor.spin( forward, drive_r_leftjoy, velocityUnits::pct );

  // allow other tasks to run
  this_thread::sleep_for( 10 );
}


/**
  * module: ARCADE DRIVE: RIGHT JOYSTICK
  * @PARAM: Left Side   ( Axis2 + Axis1 )
  * @PARAM: Right Side  ( Axis2 - Axis1 )
  * @TODO:
  *
  */
void arcadeDrive_rightJoy(){

  // DEADBAND, set to 0 if below the deadband threshold
  if( abs( forward_pct_rightjoy ) < deadband ) forward_pct_rightjoy = 0;
  if( abs( turn_pct_rightjoy    ) < deadband ) turn_pct_rightjoy = 0;

  // send to motors
  // left arcade motors
  LFmotor.spin( forward, drive_l_rightjoy, velocityUnits::pct );
  LBmotor.spin( forward, drive_l_rightjoy, velocityUnits::pct );
  // right arcade motors
  RFmotor.spin( forward, drive_r_rightjoy, velocityUnits::pct );
  RBmotor.spin( forward, drive_r_rightjoy, velocityUnits::pct );

  // allow other tasks to run
  this_thread::sleep_for( 10 );
}
