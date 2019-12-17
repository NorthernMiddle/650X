/*----------------------------------------------------------------------------------------*/
/*                                                                                        */
/*   	Module:       arcadeDriveLeftJoy.cpp                                                */
/*   	Author:       NMS_RP                                                                */
/*   	Created:      16 Dec 2019                                                           */
/*  	Description:  arcade drive left joystick with deadband and cubic                    */
/*                   power input for VEX V5                                               */
/*                                                                                        */
/*----------------------------------------------------------------------------------------*/

// deadband threshold
const int deadband = 15; 

/** arcade drive variable intializations
  * left joystick variable intializations
  * - deadband variables intializations
  * - drive variables intializations
  *
  * right joystick variable intializations
  * - deadband variables intializations
  * - drive variables intializations
  */
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


/** Cubic Scale Factor for Arcade Drive Power
  * Functions used to achieve more sensitivity at low motor power
  * used for precise movements while still being able to use 100% power
  */
int cube_drive_l_leftjoy(int drive_l_leftjoy){				// arcade drive cube scale factor left joystick control
    return  pow(drive_l_leftjoy/100.0, 3.0)*100.0;
}
int cube_drive_r_leftjoyl(int drive_r_leftjoy){				// arcade drive cube scale factor left joystick control
    return  pow(drive_r_leftjoy/100.0, 3.0)*100.0;
}
int cube_drive_l_rightjoy(int drive_l_rightjoy){			// arcade drive cube scale factor right joystick control
    return  pow(drive_l_rightjoy/100.0, 3.0)*100.0;
}
int cube_drive_r_rightjoyl(int drive_r_rightjoy){			// arcade drive cube scale factor right joystick control
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
  if( abs( forward_pct_leftjoy ) < deadband ) forward_pct_leftjoy = 0;
  if( abs( turn_pct_leftjoy    ) < deadband ) turn_pct_leftjoy = 0;

  // send to motors
  // --- left arcade motors ---
  LFmotor.spin( forward, cube_drive_l_leftjoy, velocityUnits::pct );
  LBmotor.spin( forward, cube_drive_l_leftjoy, velocityUnits::pct );
  // --- right arcade motors ---
  RFmotor.spin( forward, cube_drive_r_leftjoy, velocityUnits::pct );
  RBmotor.spin( forward, cube_drive_r_leftjoy, velocityUnits::pct );

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
  LFmotor.spin( forward, cube_drive_l_rightjoy, velocityUnits::pct );
  LBmotor.spin( forward, cube_drive_l_rightjoy, velocityUnits::pct );
  // right arcade motors
  RFmotor.spin( forward, cube_drive_r_rightjoy, velocityUnits::pct );
  RBmotor.spin( forward, cube_drive_r_rightjoy, velocityUnits::pct );

  // allow other tasks to run
  this_thread::sleep_for( 10 );
}
