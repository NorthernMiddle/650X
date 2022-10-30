/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.cpp                                                 */
/*    Author:       LoJac10                                                   */
/*    Created:      Oct 30th, 2022                                            */
/*    Description:  15-Second Autonomous Routines                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

/**	============================= Autonomous Routine Definitions =============================
  *
  *	Red Left 1 - RL1 - <narative of goal of this auton program>
  *	Red Left 2 - RL2 - <narative of goal of this auton program>
  *	Red Right 1 - RR1 - <narative of goal of this auton program>
  *	Red Right 2 - RR2 - <narative of goal of this auton program>
  *
  *	Blue Left 1 - BL1 - <narative of goal of this auton program>
  * Blue Left 2 - BL2 - <narative of goal of this auton program>
  *	Blue Right 1 - BR1 - <narative of goal of this auton program>
  *	Blue Right 2 - BR2 - <narative of goal of this auton program>
  *
  * ============================================================================================ */

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Red Left 1                                          */
/*-----------------------------------------------------------------------------*/
void Auton_RL1() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("RL1 is running..."); 

  // insert Autonomous RL1 Program Here...
  task::sleep(500);   
}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Red Left 2                                          */
/*-----------------------------------------------------------------------------*/
void Auton_RL2() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("RL2 is running...");

  // insert Autonomous RL2 Program Here...
  task::sleep(500);   
}  

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Red Right 1                                         */
/*-----------------------------------------------------------------------------*/
void Auton_RR1() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("RR1 is running...");

  // insert Autonomous RR1 Program Here...
  task::sleep(500);   
}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Red Right 2                                         */
/*-----------------------------------------------------------------------------*/
void Auton_RR2() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("RR2 is running...");

  // insert Autonomous RR2 Program Here...
  task::sleep(500);   
}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Blue Left 1                                         */
/*-----------------------------------------------------------------------------*/
void Auton_BL1() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("BL1 is running...");

  // insert Autonomous BL1 Program Here...
  task::sleep(500);   
}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Blue Left 2                                         */
/*-----------------------------------------------------------------------------*/
void Auton_BL2() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("BL2 is running...");

  // insert Autonomous BL2 Program Here...
  task::sleep(500);   
}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Blue Right 1                                        */
/*-----------------------------------------------------------------------------*/
void Auton_BR1() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("BR1 is running...");

  // insert Autonomous BR1 Program Here...
  task::sleep(500);   
}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous Blue Right 2                                        */
/*-----------------------------------------------------------------------------*/
void Auton_BR2() {
  Brain.Screen.clearScreen();
  Brain.Screen.newLine();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("BR2 is running...");

  // insert Autonomous BR2 Program Here...
  task::sleep(500);   
}
