#ifndef TRAYLIFT_HPP
#define TRAYLIFT_HPP

#include "vex.hpp"

// traylift speed variable
int trayLiftSpeedPCT = 100;       

/** 	--- Tray Movement Shortend Function Call Setup ---
   *  tray lift up:     	cmd runs tray lift up manually by pressing of Button R1 (Manual Operation)
   *  tray lift down:  	  cmd runs tray lift down manually by pressing of Button R2 (Manual Operation)
   *  tray lift reset:  	cmd runs tray lift down from BUTTONDOWN press till limit switch is triggered (Automatic Reset)
   */
void trayLiftSpinUp(){
  TrayLiftmotor.spin( reverse, trayLiftSpeedPCT, velocityUnits::pct );
}

void trayLiftSpinDown(){
  TrayLiftmotor.spin( forward, trayLiftSpeedPCT, velocityUnits::pct );
}

///////////////////////////////////////////////////
//
// --- Tray Lift Thread ---
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
    TrayLiftmotor.stop( brakeType::brake );
    manual_mode = true;
  
  // Manual: Tray Down by ButtonR2 with Hard Stop by Limit Switch   
  if(( manual_mode == true ) && ((Controller1.ButtonR2.pressing()) == true ))
    manual_mode = true;
    while(( manual_mode == true ) && ( Controller1.ButtonR2.pressing() == true ) && 
    ( TrayLiftlimit.pressing() == false )){ trayLiftSpinDown(); }
    TrayLiftmotor.stop( brakeType::brake );
    manual_mode = true;
  
  // Automatic: Tray Down Return by ButtonDown Press with Hard Stop by Limit Switch
  if(( Controller1.ButtonDown.pressing()) == true )
    manual_mode = false;
    while(( manual_mode == false ) && (( TrayLiftlimit.pressing()) == false )){
    trayLiftSpinDown(); }
    TrayLiftmotor.stop( brakeType::brake );
    manual_mode = true;
	
	// Allow other tasks to run
  // don't hog the cpu :)
  vex::this_thread::sleep_for( 10 );
}

#endif

