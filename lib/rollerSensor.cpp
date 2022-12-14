/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       roller.cpp                                                */
/*    Author:       LoJac10                                                   */
/*    Created:      13th Dec 2022                                             */
/*    Description:  A module to use the optical sensor to turm a colored      */
/*                  roller to either a color of blue or red                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;


int roller(){

  Intake.setVelocity(100, velocityUnits::pct); 
  while(1) { 

    rollerOptical.setLightPower(100, percent); 
    rollerOptical.setLight(ledState::on); 
    
    // when alliance status is blue
    if( (allianceStatus == 1) && (rollerOptical.color() == vex::red) ) {
      Brain.Screen.printAt( 10, 20, "RED detected     ");

      // turn intake till blue
      Intake.spin(fwd);
      waitUntil(rollerOptical.color() == vex::blue);
      Intake.stop(brakeType::brake);
    }
    else
    // when alliance ststus is red
    if( (allianceStatus == 0) && (rollerOptical.color() == vex::blue) ) {
      Brain.Screen.printAt( 10, 20, "BLUE detected    ");

      // turn intake till red
      Intake.spin(fwd);
      waitUntil(rollerOptical.color() == vex::red);
      Intake.stop(brakeType::brake);
    }
    else {
      Brain.Screen.printAt( 10, 20, "no color detected");          
    }

    // Turn Optical Sensor LED Off
    rollerOptical.setLight(ledState::off); 
    
    // Allow other tasks to run
    this_thread::sleep_for( 10 );
  }
}
