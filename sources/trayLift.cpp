/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       trayLift.cpp                                              */
/*    Author:       NMS_RP                                                    */
/*    Created:      Thur Oct 24 2019                                          */
/*    Description:  Tray Lift Control                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// --- traylift.cpp ---
#include "vex.h"
using namespace vex;

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
	
	/* You must sleep threads by using the 'this_thread::sleep_for(unit in
    msec)' command to prevent this thread from using all of the CPU's
    resources. */
  vex::this_thread::sleep_for( 25 );
    
  }
  /* A threads's callback must return an int, even though the code will never
  get here. You must return an int here. Threads can exit, but this one does not. */
  return( 0 );
}
