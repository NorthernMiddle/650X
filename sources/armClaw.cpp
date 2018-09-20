/**
 * arm.cpp - arm control program
 *
 * This code has been created for VEX650 "NMS Robotics" Turning Point
 * This example program shows how to program the V5 Clawbot to use remote
 *  control values to move your robot's arm.
 * @TODO:
 * @TODO:
 */

void armControl( void ){
   //Raise the Arm Motor if the Button Up is pressed
   if(Controller1.ButtonUp.pressing()) {
        armMotor.spin(directionType::fwd, armSpeedPCT, velocityUnits::pct);
    }
   //Lower the Arm Motor if the Button Down is pressed
    else if(Controller1.ButtonDown.pressing()) {
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
