#include "vex.h"
using namespace vex;

///////////////////////////////////////////////////////////////////
//
// Set Motor Functions
//  - this sets motors between -12000 and 12000.  i'm used to
//  - -100 to 100, so the "scale" variable lets me use that as
//  - inputs and scales it to -12000 to 12000
//
///////////////////////////////////////////////////////////////////

// Set voltage <-- power setting for drive
const int SCALE = 120;
void set_tank(int l, int r) {
  LeftFront.spin(fwd, l * SCALE, voltageUnits::mV);
  LeftBack.spin(fwd, l * SCALE, voltageUnits::mV);
  RightFront.spin(fwd, r * SCALE, voltageUnits::mV);
  RightBack.spin(fwd, r * SCALE, voltageUnits::mV);
  
  void set_intake(int input) {
  Intake.spin(fwd, input * SCALE, voltageUnits::mV);
}

void set_indexer(int pos, int speed) {
  Indexer.startRotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct);
}

void set_flywheel(int input) {
  Flywheel.spin(fwd, input * SCALE, voltageUnits::mV);
  Flywheel2.spin(fwd, input * SCALE, voltageUnits::mV);
}
