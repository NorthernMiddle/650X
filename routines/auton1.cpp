/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.cpp                                                 */
/*    Author:       NMS_RP                                                    */
/*    Created:      03 Dec 2019                                               */
/*    Description:  15-Second Autonomous Routines                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

#define TRAY_THRESHOLD 7.65

/**	============================= Red Alliance Autonomous Routines =============================
  *
  *	Auton_RL1 Alliance Routine: GOAL: 1-PT: Push block into corner
  *	Auton_RL2 Alliance Routine: GOAL: 5-PT: Use pre-load and four blocks in single line to stack in corner 
  *	Auton_RR1 Alliance Routine: GOAL: 1-PT: Push block into corner
  *	Auton_RR2 Alliance Routine: GOAL: 3-PT: Use pre-load and two blocks to stack in corner
  *
  */

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Straight                                            */
/*-----------------------------------------------------------------------------*/
void Auton_Straight() {
  /* --- GOAL: 1-PT ---- */
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Program Straight Ahead is running"); 

  Drivetrain.driveFor( forward, 27, inches, 90, rpm, true );                                            // go straight to lip of score barrier.
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500);                                                                                     // time out for 1/2-second
  Drivetrain.driveFor( reverse, 15, inches, 90, rpm, true );                                            // reverse just a little bit to clear blocks
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500);   

}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Red Left                                            */
/*-----------------------------------------------------------------------------*/
void Auton_RL() {
  /* --- GOAL: 5-PT --- */
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Program Red Left is running");

  //TrayLiftmotors.setRotation(0, rotationUnits::rev);                                                     // set tray motor encoder to zero 
  TrayLiftCentermotor.setRotation(0, rotationUnits::rev);
  Spinners.spin(forward, 100, rpm);                                                                     // start spinners to pick up blocks
  wait(500, msec);
  Drivetrain.driveFor( forward, 30, inches, 70, rpm, true );                                            // go forward to  grab pre-load and 1st green block
  Spinners.stop();                                                                                      // spinners stop
  Drivetrain.driveFor( reverse, 3.5, inches, 50, rpm, true );                                             // back up to get in line for turn for 2nd green block
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500);                                                                                     // time out for 1/2-second

  Drivetrain.turnFor(turnType::left, 70, rotationUnits::deg, 50, velocityUnits::rpm);                  // turn right to line up another block next to alliance zone
  Drivetrain.stop();                                                                                    // stop
  task::sleep(250);                                                                                     // time out for 1/4-second
                                                                                       
  Drivetrain.driveFor( forward, 2, inches, 60, rpm, true );                                             // go fwd just a little to pick up 2nd cube; start rolling to straighten out with low power
  Spinners.spin(forward, 100, rpm);                                                                     // start spinners to pick up 2nd green block
  Drivetrain.driveFor( forward, 23, inches, 60, rpm, true );                                            // finish out straight movement to pick up 2nd block
  Spinners.stop();                                                                                      // spinners stop
  Drivetrain.stop();                                                                                    // drive stop
  task::sleep(500);                                                                                     // time out for 1/2-second

  Drivetrain.turnFor(turnType::left, 32, rotationUnits::deg, 20, velocityUnits::pct);                   // turn right
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500); 

  Drivetrain.driveFor( forward, 12, inches, 60, rpm, true );                                            // go fwd
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500);                                                                                     // time out for 1/2-second

  TrayLiftCentermotor.setReversed(false); 
  // TrayLiftExtramotor.setReversed(true);                                                                        // time out for 1/2-second
  // TrayLiftmotors.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, true );           // raise tray to stack blocks
  TrayLiftCentermotor.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, true ); 
  task::sleep(1000);  
  Drivetrain.driveFor( reverse, 15, inches, 100, rpm, true );                                           // reverse just a little bit to clear blocks
  while(TrayLiftlimit.value() != 1){                                                                    // while tray limit value does not equal 1 run tray motor in reverse
    //TrayLiftmotors.spin(directionType::rev, 100, pct);}                                                  // return tray to down position while backing up
    TrayLiftCentermotor.spin(directionType::rev, 100, pct);}
  //TrayLiftmotors.stop(brake);                                                                            // tray lift brake and hold
  TrayLiftCentermotor.stop(brake);
  Drivetrain.stop();                                                                                    // stop
  //TrayLiftmotors.setRotation(0, rotationUnits::rev);                                                     // set tray motor encoder to zero 
  TrayLiftCentermotor.setRotation(0, rotationUnits::rev);
  TrayLiftCentermotor.setReversed(true); 
  //TrayLiftExtramotor.setReversed(false); 
}  

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Red Right                                           */
/*-----------------------------------------------------------------------------*/
void Auton_RR() {
  /* --- GOAL: 5-PT --- */
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Auton Red Right is running");

  LeftSide.setRotation(0, rotationUnits::rev);
  RightSide.setRotation(0, rotationUnits::rev);
  Brain.Screen.newLine();
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Left Back Motor Encoder Value is: %d", LBmotor.position(rotationUnits::rev));
  Brain.Screen.newLine();
  Brain.Screen.print("Right Back Motor Encoder Value is: %d", RBmotor.position(rotationUnits::rev));

  TrayLiftCentermotor.setRotation(0, rotationUnits::rev);                                               // set tray motor encoder to zero
  
  Spinners.spin(forward, 80, velocityUnits::pct);                                                      // start spinners to bring blocks in
  wait(500, msec);                                                                                      // wait 1/2 sec to get spinners working 
                              
  Drivetrain.driveFor(forward, 5, inches, 50, rpm, true);                                              // go straight to line up with 4 single-stacked blocks to bring into intake.
  Drivetrain.driveFor(forward, 45, inches, 100, rpm, true);                                              // go straight to line up with 4 single-stacked blocks to bring into intake.
  Drivetrain.stop();
  LeftSide.setRotation(0, rotationUnits::rev);
  RightSide.setRotation(0, rotationUnits::rev);
  Spinners.stop();                                                                                      // stop spinners
  /*
  Spinners.setStopping(hold);                                                                           // set spinner brake type to hold; in order to hold blocks
  Drivetrain.turnFor(turnType::right, 112, rotationUnits::deg, 50, velocityUnits::rpm);                  // turn left to line up with single-stacked blocks
  Drivetrain.driveFor(forward, 40, inches, 90, rpm, true);                                            // go forward running intakes to bring blocks into robot
  Drivetrain.stop();
  LeftSide.setRotation(0, rotationUnits::rev);
  RightSide.setRotation(0, rotationUnits::rev);                                                                                    // stop
  task::sleep(500); 

  TrayLiftCentermotor.setReversed(false); 
  //TrayLiftExtramotor.setReversed(true);                                                                 // time out for 1/2-second
  //TrayLiftExtramotor.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, false);      // raise tray to stack blocks
  TrayLiftCentermotor.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, true);
  Spinners.spin(reverse, 15, velocityUnits::rpm);
  wait(750, msec);
  Spinners.stop();
  task::sleep(1000);  

  Drivetrain.driveFor(reverse, 8, inches, 35, rpm, true);
  Drivetrain.driveFor(reverse, 15, inches, 100, rpm, true);                                             // reverse just a little bit to clear blocks
  while(TrayLiftlimit.value() != 1){                                                                    // while tray limit value does not equal 1 run tray motor in reverse
    //TrayLiftmotors.spin(reverse, 100, pct);}                                                 // return tray to down position while backing up
    TrayLiftCentermotor.spin(reverse,100,pct);}
  //TrayLiftmotors.stop(brake);                                                                           // tray lift brake and hold
  TrayLiftCentermotor.stop(brake);
  Drivetrain.stop();                                                                                    // stop
  //TrayLiftmotors.setRotation(0, rotationUnits::rev);                                                    // set tray motor encoder to zero
  TrayLiftCentermotor.setRotation(0,rotationUnits::rev);
  TrayLiftCentermotor.setReversed(true); 
  //TrayLiftExtramotor.setReversed(false);  
  */ 
  this_thread::sleep_for(10);
}


/**	============================= Blue Alliance Autonomous Routines =============================
  *
  *	Auton_BL Alliance Routine: GOAL: 5-PT: Use pre-load and four blocks in single line to stack in corner 
  *	Auton_BR Alliance Routine: GOAL: 3-PT: Use pre-load and two blocks to stack in corner
  *
  */


/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Blue Left                                           */
/*-----------------------------------------------------------------------------*/
void Auton_BL() {
  /* --- GOAL: 5-PT --- */
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Auton Blue Left is running");

  LeftSide.setRotation(0, rotationUnits::rev);
  RightSide.setRotation(0, rotationUnits::rev);

  TrayLiftCentermotor.setRotation(0, rotationUnits::rev);                                               // set tray motor encoder to zero
  //TrayLiftExtramotor.setRotation(0, rotationUnits::rev);                                               
  Spinners.spin(forward, 200, velocityUnits::rpm);                                                      // start spinners to bring blocks in
  wait(250, msec);                                                                                      // wait 1/2 sec to get spinners working 
                                
  Drivetrain.driveFor(forward, 5, inches, 50, rpm, true);                                              // go straight to line up with 4 single-stacked blocks to bring into intake.
  Drivetrain.driveFor(forward, 45, inches, 100, rpm, true);                                              // go straight to line up with 4 single-stacked blocks to bring into intake.
  Drivetrain.stop();
  LeftSide.setRotation(0, rotationUnits::rev);
  RightSide.setRotation(0, rotationUnits::rev);
  Spinners.stop();                                                                                      // stop spinners

  Spinners.setStopping(hold);                                                                           // set spinner brake type to hold; in order to hold blocks
  Drivetrain.turnFor(turnType::left, 124, rotationUnits::deg, 50, velocityUnits::rpm);                  // turn left to line up with single-stacked blocks
  Drivetrain.driveFor(forward, 40, inches, 90, rpm, true);                                            // go forward running intakes to bring blocks into robot
  Drivetrain.stop();
  LeftSide.setRotation(0, rotationUnits::rev);
  RightSide.setRotation(0, rotationUnits::rev);                                                                                    // stop
  task::sleep(500); 

  TrayLiftCentermotor.setReversed(false); 
  //TrayLiftExtramotor.setReversed(true);                                                                 // time out for 1/2-second
  //TrayLiftExtramotor.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, false);      // raise tray to stack blocks
  TrayLiftCentermotor.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, true);
  Spinners.spin(reverse, 15, velocityUnits::rpm);
  wait(250, msec);
  Spinners.stop();
  task::sleep(1000);  

  Drivetrain.driveFor(reverse, 8, inches, 35, rpm, true);
  Drivetrain.driveFor(reverse, 15, inches, 100, rpm, true);                                             // reverse just a little bit to clear blocks
  while(TrayLiftlimit.value() != 1){                                                                    // while tray limit value does not equal 1 run tray motor in reverse
    //TrayLiftmotors.spin(reverse, 100, pct);}                                                 // return tray to down position while backing up
    TrayLiftCentermotor.spin(reverse, 100, pct);}
  //TrayLiftmotors.stop(brake);                                                                           // tray lift brake and hold
  TrayLiftCentermotor.stop(brake);
  Drivetrain.stop();                                                                                    // stop
  //TrayLiftmotors.setRotation(0, rotationUnits::rev);                                                    // set tray motor encoder to zero
  TrayLiftCentermotor.setRotation(0, rotationUnits::rev);
  TrayLiftCentermotor.setReversed(true); 
  //TrayLiftExtramotor.setReversed(false);   
}


/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Blue Right                                          */
/*-----------------------------------------------------------------------------*/
void Auton_BR() {
  /* --- GOAL: 3-PT --- */
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Auton Blue Right is running"); 
   
  //TrayLiftmotors.setRotation(0, rotationUnits::rev);
  TrayLiftCentermotor.setRotation(0,rotationUnits::rev);
  Spinners.spin(forward, 100, rpm);                                                                     // start spinners to pick up blocks
  Drivetrain.driveFor( forward, 26, inches, 80, rpm, true );                                            // go forward to  grab pre-load and 1st green block
  Spinners.stop();                                                                                      // spinners stop
  Drivetrain.driveFor( reverse, 4, inches, 50, rpm, true );                                             // back up to get in line for turn for 2nd green block
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500);                                                                                     // time out for 1/2-second

  Drivetrain.turnFor(turnType::right, 68, rotationUnits::deg, 50, velocityUnits::rpm);                  // turn right to line up another block next to alliance zone
  Drivetrain.stop();                                                                                    // stop
  task::sleep(250);                                                                                     // time out for 1/4-second
                                                                                       
  Drivetrain.driveFor( forward, 2, inches, 60, rpm, true );                                             // go fwd just a little to pick up 2nd cube; start rolling to straighten out with low power
  Spinners.spin(forward, 100, rpm);                                                                     // start spinners to pick up 2nd green block
  Drivetrain.driveFor( forward, 23, inches, 60, rpm, true );                                            // finish out straight movement to pick up 2nd block
  Spinners.stop();                                                                                      // spinners stop
  Drivetrain.stop();                                                                                    // drive stop
  task::sleep(500);                                                                                     // time out for 1/2-second

  Drivetrain.turnFor(turnType::right, 33, rotationUnits::deg, 20, velocityUnits::pct);                  // turn right
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500); 

  Drivetrain.driveFor(forward, 11, inches, 60, rpm, true);                                              // go fwd positioning stack tray into score zone
  Drivetrain.stop();                                                                                    // stop
  task::sleep(500);                                                                                     // time out for 1/2-second

  TrayLiftCentermotor.setReversed(false); 
  //TrayLiftExtramotor.setReversed(true);                                                                 // time out for 1/2-second
  //TrayLiftmotors.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, true );          // raise tray to stack blocks
  TrayLiftCentermotor.rotateTo(TRAY_THRESHOLD, rotationUnits::rev, 100, velocityUnits::rpm, true);
  task::sleep(1000);  
  Drivetrain.driveFor( reverse, 15, inches, 100, rpm, true );                                           // reverse just a little bit to clear blocks
  while(TrayLiftlimit.value() != 1){                                                                    // while tray limit value does not equal 1 run tray motor in reverse
    //TrayLiftmotors.spin(directionType::rev, 100, pct);}                                                 // return tray to down position while backing up
    TrayLiftCentermotor.spin(directionType::rev, 100, pct);}
  //TrayLiftmotors.stop(brake);                                                                           // tray lift brake and hold
  TrayLiftCentermotor.stop(brake);
  Drivetrain.stop();                                                                                    // stop
  //TrayLiftmotors.setRotation(0, rotationUnits::rev);                                                    // set tray motor encoder to zero                                                                        
  TrayLiftCentermotor.setRotation(0,rotationUnits::rev);
  TrayLiftCentermotor.setReversed(true); 
  //TrayLiftExtramotor.setReversed(false);   
}
