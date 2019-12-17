/*----------------------------------------------------------------------------------------*/
/*                                                                                        */
/*   	Module:       trayLift.cpp                                                        */
/*   	Author:       NMS_RP                                                               */
/*   	Created:      16 Dec 2019                                                          */
/*  	Description:  Lift Func for Cube Tray - Tower Takeover           		*/
/*                                                                                        */
/*----------------------------------------------------------------------------------------*/

// traylift speed variable
int trayLiftSpeedPCT = 100;       

/** 	--- Tray Movement Shortend Function Call Setup ---
   *  tray lift up:     	cmd runs tray lift up manually by pressing of Button R1 (Manual Operation)
   *  tray lift down:  	  	cmd runs tray lift down manually by pressing of Button R2 (Manual Operation)
   *  tray lift reset:  	cmd runs tray lift down from BUTTONDOWN press till limit switch is triggered (Automatic Reset)
   */
void trayLiftSpinUp(){
  TL.spin( reverse, trayLiftSpeedPCT, velocityUnits::pct );
}

void trayLiftSpinDown(){
  TLmotor.spin( forward, trayLiftSpeedPCT, velocityUnits::pct );
}

///////////////////////////////////////////////////
//
// --- Tray Lift Function ---
//
///////////////////////////////////////////////////

// declare state variable for tray lift
bool manual_mode = true;          

void TLSelection(){
  // Manual: Tray Up by ButtonR1
  if((( manual_mode == true ) && (( Controller1.ButtonR1.pressing()) == true )))
  manual_mode = true;
  while(( manual_mode == true ) && (( Controller1.ButtonR1.pressing() == true))){
    trayLiftSpinUp();}
    TLmotor.stop( brakeType::brake );
    manual_mode = true;
  
  // Manual: Tray Down by ButtonR2 with Hard Stop by Limit Switch   
  if(( manual_mode == true ) && ((Controller1.ButtonR2.pressing()) == true ))
    manual_mode = true;
    while(( manual_mode == true ) && ( Controller1.ButtonR2.pressing() == true ) && 
    ( TrayLiftlimit.pressing() == false )){ trayLiftSpinDown(); }
    TLmotor.stop( brakeType::brake );
    manual_mode = true;
  
  // Automatic: Tray Down Return by ButtonDown Press with Hard Stop by Limit Switch
  if(( Controller1.ButtonDown.pressing()) == true )
    manual_mode = false;
    while(( manual_mode == false ) && (( TrayLiftlimit.pressing()) == false )){
    trayLiftSpinDown(); }
    TLmotor.stop( brakeType::brake );
    manual_mode = true;
	
/* Allow other tasks to run; don't hog the cpu :) */
  vex::this_thread::sleep_for( 10 );
}
