/**
 * arm.cpp - arm control program
 *
 * This code has been created for VEX650 "NMS Robotics" Turning Point
 * 
 * @TODO: Implement preset heights for Button presses
 * @TODO: Implement instructions for preset heights for button press -
 *          Up Button (High Post) & Down Button (Low Post)
 * @TODO: Implement instructions for preset heights for button press - 
 *          Left Button (Min Height) & Right Button (Max Height)
 * @TODO: Implement logic for brain to decide arm movement based on arm position when either
 *          the Left Button is pressed or the Right Button is pressed.
 */

void armControl( void ){
   //Raise Arm to Max Height : Raise the Arm Motor if the Button Up is pressed
   if(Controller1.ButtonRight.pressed()) {
        armMotor.spin(directionType::fwd, armSpeedPCT, velocityUnits::pct);
    }
   //Move Arm to Preset Height of Lower Post : Move the Arm Motor to Preset Height of Lower Post
   else if(Controller1.ButtonLeft.pressed()){
      armMotor.spin(directionType:: ????
    }
   //Move Arm to Preset Height of High Post : Move the Arm Motor to the Preset Height of High Post
    else if(Controller1.ButtonRight.pressed()){
       armMotor.spin(directionType:: ????
    }
   //Lower the Arm to Min Height : Lower the Arm Motor if the Button Down is pressed
   else if(Controller1.ButtonDown.pressed()) {
        armMotor.spin(directionType::rev, armSpeedPCT, velocityUnits::pct);
    }
   //Else stop the Arm Motor and hold its current position
   else {
        armMotor.stop(brakeType::hold);
}

/**
 * claw.cpp - claw control program
 *
 * This code has been created for VEX650 "NMS Robotics" Turning Point
 * This example program shows how to program the V5 Clawbot to use remote
 *  control values to move your robot's claw.
 * @TODO:
 * @TODO:
 */

void clawControl( void ){
   //Open the Claw Motor if  the Button A is pressed
   if(Controller1.ButtonA.pressing()) {
        clawMotor.spin(directionType::fwd, clawSpeedPCT, velocityUnits::pct);
    }
   //Close the Claw Motor if  the Button Y is pressed
    else if(Controller1.ButtonY.pressing()) {
        clawMotor.spin(directionType::rev, clawSpeedPCT, velocityUnits::pct);
    }
   //Else stop the Claw Motor and hold its current position
    else {
        clawMotor.stop(brakeType::hold);
    }
}
