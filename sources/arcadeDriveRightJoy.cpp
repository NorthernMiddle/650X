/*----------------------------------------------------------------------------------------*/
/*                                                                                        */
/*   	Module:       arcadeDriveRightJoy.cpp                                               */
/*   	Author:       NMS_RP                                                                */
/*   	Created:      16 Dec 2019                                                           */
/*  	Description:   arcade drive right joystick with deadband and cubic                   */
/*                   power input for VEX V5                                               */
/*                                                                                        */
/*----------------------------------------------------------------------------------------*/

// deadband threshold
const int deadband = 15; 

/** arcade drive variable intializations
  * right joystick variable intializations
  * - deadband variables intializations
  * - drive variables intializations
  */

/* --- RIGHT JOYSTICK --- */
int forward_pct_rightjoy = Controller1.Axis2.position();
int turn_pct_rightjoy = Controller1.Axis1.position();
double drive_l_rightjoy = Controller1.Axis2.value() + Controller1.Axis1.value();   // left '+'
double drive_r_rightjoy = Controller1.Axis2.value() - Controller1.Axis1.value();   // right '-'


/** Cubic Scale Factor for Arcade Drive Power
  * Functions used to achieve more sensitivity at low motor power
  * used for precise movements while still being able to use 100% power
  */
int cube_drive_l_rightjoy(int drive_l_rightjoy){			// arcade drive cube scale factor right joystick control
    return  pow(drive_l_rightjoy/100.0, 3.0)*100.0;
}
int cube_drive_r_rightjoy(int drive_r_rightjoy){			// arcade drive cube scale factor right joystick control
    return  pow(drive_r_rightjoy/100.0, 3.0)*100.0;

///////////////////////////////////////////////////////////////
//
//  --- Arcade Drive with Deadband and Cubic Power Input ---
//
///////////////////////////////////////////////////////////////

/**
  * module: ARCADE DRIVE: LEFT JOYSTICK
  * @PARAM: Left Side   ( Axis3 + Axis4 )
  * @PARAM: Right Side  ( Axis3 - Axis4 )
  * @TODO:
  *
  */
void arcadeDrive_leftJoy(){
  // DEADBAND, set to 0 if below the deadband threshold



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
  LFmotor.spin( forward, cube_drive_l_rightjoy, velocityUnits::pct );
  LBmotor.spin( forward, cube_drive_l_rightjoy, velocityUnits::pct );
  // right arcade motors
  RFmotor.spin( forward, cube_drive_r_rightjoy, velocityUnits::pct );
  RBmotor.spin( forward, cube_drive_r_rightjoy, velocityUnits::pct );

  // allow other tasks to run
  this_thread::sleep_for( 10 );
}
