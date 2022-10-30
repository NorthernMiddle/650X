/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       operations.cpp                                            */
/*    Author:       NMS_RP                                                    */
/*    Created:      4 Jan 2020                                                */
/*    Description:  Operation control file for all driver functions           */
/*                  and thread calls                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

// constant variables
const int Deadband = 15;       // deadband threshold

// global variables
int intakeSpeedPCT = 100;     // velocity for intake spinners
int trayLiftSpeedPCT = 100;   // velocity for tray lift
bool manual_mode = true;      // declare state variable for tray lift
int LFmotorSpeed, LBmotorSpeed, RFmotorSpeed, BmotorSpeed;

/** --- Cubic Scale Factor Functions for Power Adjustment --- 
  * Description: 
  *    Functions used to achieve more sensitivity at low motor power
  *    used for precise movements while still being able to use 100% power
  * 
  */
// ceiling function, function definition, function calls for left and right joysticks
double ceil_drive_lval( double drive_lval ){            // ceiling up to whole unit double for left joy
  return ceil(drive_lval);
}

double ceil_drive_rval( double drive_rval ){            // ceiling up to whole unit double for right joy
  return ceil(drive_rval);
}

// cube function, function definition, function calls for left and right joysticks
double cube_drive_lval( double ceildrive_lval ){			  // tank drive cube scale factor left joy
    return  pow(ceildrive_lval/100.0, 3.0)*100.0;
}

double cube_drive_rval( double ceildrive_rval ){				// tank drive cube scale factor right joy
    return  pow(ceildrive_rval/100.0, 3.0)*100.0;
}

/** --- tankDrive_f is a callback function ---
  * Description:
  *   Function for tank drive. Function to be registered to a thread for continuous use.
  *   Function registered to thread tankdrive_t
  *
  */
int tankDrive_f(){
 int count = 0;
 while(true){
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("TankDrive has iterated %d times", count);
  count++;

  // tank drive func --- variable intializations
  double drive_lval = Controller1.Axis3.position();          // tank drive control
  double drive_rval = Controller1.Axis2.position();          // tank drive control
  
  
  // deadband, set to 0 if below the deadband value
  if( fabs( drive_lval ) < Deadband ) drive_lval = 0;
  if( fabs( drive_rval ) < Deadband ) drive_rval = 0;
 
  double ceildrive_lval = ceil_drive_lval( drive_lval );
  double ceildrive_rval = ceil_drive_rval( drive_rval );

  double cubedrive_lval = cube_drive_lval( ceildrive_lval );
  double cubedrive_rval = cube_drive_rval( ceildrive_rval );
    
  // just for fun, display the values
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Raw %6.2f cube %6.2f", drive_lval, cubedrive_lval );
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Raw %6.2f cube %6.2f", drive_rval, cubedrive_rval );

  /* --- send to motors --- */
  // left tank motors
  LFmotor.spin( directionType::fwd, cubedrive_lval, velocityUnits::pct );
  LBmotor.spin( directionType::fwd, cubedrive_lval, velocityUnits::pct );
  // right tank motors
  RFmotor.spin( directionType::fwd, cubedrive_rval, velocityUnits::pct );
  RBmotor.spin( directionType::fwd, cubedrive_rval, velocityUnits::pct );

  /* You must sleep threads by using the 'this_thread::sleep_for(unit in
    msec)' command to prevent this thread from using all of the CPU's
    resources. */
  this_thread::sleep_for( 25 );
    }

/* A threads's callback must return an int, even though the code will never
  get here. You must return an int here. Threads can exit, but this one does not. */
return 0;
}


/** --- intake function ---
  * Description:
  *   Function to run intake spinners for VRC Tower Takeover. Spinners will pull
  *   cubes into tray lift mechanism.
  * @PARAM: Pressing L1 to run intake spinners to pull blocks into the tray
  * @PARAM: Pressing L2 to run intake spinners to push blocks out of the tray
  * @PARAM: Not pressing L1 or L2 does not run intake spinners. Intake spinners hold in place.
  *
  **/
int intake_f(){
  int count = 0;
  while(true){
  Brain.Screen.setCursor(2,1); // set cursor line 2 position 1 on LCD screen
  Brain.Screen.print("Intake has iterated %d times", count);
  count++;

    if(Controller1. ButtonL1.pressing()){
      L_Intake.spin( reverse, intakeSpeedPCT, velocityUnits::pct );
      R_Intake.spin( reverse, intakeSpeedPCT, velocityUnits::pct );
    }
    else if(Controller1.ButtonL2.pressing()){
      L_Intake.spin( forward, intakeSpeedPCT, velocityUnits::pct );
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

//------------------------------------------------------------------------------------------------------------------------
/** 	--- Tray Movement Shortend Function Call Setup ---
   *  tray lift up:     	cmd runs tray lift up manually by pressing of Button R1 (Manual Operation)
   *  tray lift down:  	  cmd runs tray lift down manually by pressing of Button R2 (Manual Operation)
   *  tray lift reset:  	cmd runs tray lift down from BUTTONDOWN press till limit switch is triggered (Automatic Reset)
   */
void trayLiftSpinUp(){
  TrayLiftCentermotor.spin(forward, trayLiftSpeedPCT, velocityUnits::pct);
  //TrayLiftExtramotor.spin(reverse, trayLiftSpeedPCT, velocityUnits::pct);
}

void trayLiftSpinDown(){
  TrayLiftCentermotor.spin(reverse, trayLiftSpeedPCT, velocityUnits::pct);
  //TrayLiftExtramotor.spin(forward, trayLiftSpeedPCT, velocityUnits::pct);
}

///////////////////////////////////////////////////
//
// --- Tray Lift Thread ---
//
///////////////////////////////////////////////////

     
/** --- tray lift function ---
  * Description:
  *   Function to control tray lift mechanism for cube stacking
  * @PARAM: Pressing BUTTON R1 to raise tray lift mechanism
  * @PARAM: Pressing BUTTON R2 to lower tray lift mechanism
  * @PARAM: Press BUTTON DOWN to lower tray lift until automatic stop by limit switch
  *
  **/
int trayLift_f(){
  int count = 0;
  while(true){
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Tray Lift has iterated %d times", count);
  count++;

  // Manual: Tray Up by ButtonR1
  if((( manual_mode == true ) && (( Controller1.ButtonR1.pressing()) == true )))
  manual_mode = true;
  while(( manual_mode == true ) && (( Controller1.ButtonR1.pressing() == true))){
    trayLiftSpinUp();}
    //TrayLiftmotors.stop( brakeType::brake ); !** Because they only have (1) lift motor **
    TrayLiftCentermotor.stop(brakeType::brake);
    manual_mode = true;
  
  // Manual: Tray Down by ButtonR2 with Hard Stop by Limit Switch   
  if(( manual_mode == true ) && ((Controller1.ButtonR2.pressing()) == true ))
    manual_mode = true;
    while(( manual_mode == true ) && ( Controller1.ButtonR2.pressing() == true ) && 
    ( TrayLiftlimit.pressing() == false )){ trayLiftSpinDown(); }
    //TrayLiftmotors.stop( brakeType::brake ); !** Because they only have (1) lift motor **
    TrayLiftCentermotor.stop(brakeType::brake);
    manual_mode = true;
  
  // Automatic: Tray Down Return by ButtonDown Press with Hard Stop by Limit Switch
  if(( Controller1.ButtonDown.pressing()) == true )
    manual_mode = false;
    while(( manual_mode == false ) && (( TrayLiftlimit.pressing()) == false )){
    trayLiftSpinDown(); }
    //TrayLiftmotors.stop( brakeType::brake ); !** Because they only have (1) lift motor **
    TrayLiftCentermotor.stop(brakeType::brake);
    manual_mode = true;
	
	/* You must sleep threads by using the 'this_thread::sleep_for(unit in
    msec)' command to prevent this thread from using all of the CPU's
    resources. */
  vex::this_thread::sleep_for( 25 );
    
  }
  /* A threads's callback must return an int, even though the code will never
  get here. You must return an int here. Threads can exit, but this one does not. */
  return( 0 );
}
