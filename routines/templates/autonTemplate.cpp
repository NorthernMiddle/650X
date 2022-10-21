/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.h                                                   */
/*    Author:       NMS_RP                                                    */
/*    Created:      03 Dec 2019                                               */
/*    Description:  15-Second Autonomous Routines                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/


/**	--- Red Alliance Autonomous Routines ---
  *
  *	Red 1 Alliance Routine: [ Description ]
  *	Red 2 Alliance Routine: [ Description ]
  *	Red 3 Alliance Routine: [ Description ]
  *	Red 4 Alliance Routine: [ Description ]
  *
  */
void Auton_Red01() {
  // enter Red Auton #1 code here...
}

void Auton_Red02() {
  // enter Red Auton #2 code here...
}

void Auton_Red03() {
  // enter Red Auton #3 code here...
}

void Auton_Red04() {
  // enter Red Auton #4 code here...
}


/**	--- Blue Alliance Autonomous Routines ---
  *
  *	Blue 1 Alliance Routine: [ Description ]
  *	Blue 2 Alliance Routine: [ Description ]
  *	Blue 3 Alliance Routine: [ Description ]
  *	Blue 4 Alliance Routine: [ Description ]
  *
  */
void Auton_Blue01() {
  // enter Blue Auton #1 code here...
}

void Auton_Blue02() {
  // enter Blue Auton #2 code here...
}

void Auton_Blue03() {
  // enter Blue Auton #3 code here...
}

void Auton_Blue04() {
  // enter Blue Auton #4 code here...
}


/////////////////////////////////////////////////////
//
// --- Alliance Autonomous Routines Selector ---
//
/////////////////////////////////////////////////////

std::string autonRoutines[] = { "Red01", "Red02", "Red03", "Red04", "Blue01", "Blue02", "Blue03", "Blue04" };
void goAuton(int autonomousSelection) {
    switch( autonomousSelection ) {
        default: case 0:
            // Auton Red01 Selected
            Brain.Screen.printAt( 60, 125, "Auton Red01 Selected ");
            Auton_Red01();
            break;
        case 1:
            // Auton Red02 Selected
            Brain.Screen.printAt( 60, 125, "Auton Red02 Selected ");
            Auton_Red02();
            break;
        case 2:
            // Auton Red03 Selected
            Brain.Screen.printAt( 60, 125, "Auton Red03 Selected ");
            Auton_Red03();
            break;
        case 3:
            // Auton Red04 Selected
            Brain.Screen.printAt( 60, 125, "Auton Red04 Selected ");
            Auton_Red04();
            break;
        case 4:
            // Auton Blue01 Selected
            Brain.Screen.printAt( 60, 125, "Auton Blue01 Selected ");
            Auton_Blue01();
            break;
        case 5:
            // Auton Blue02 Selected
            Brain.Screen.printAt( 60, 125, "Auton Blue02 Selected ");
            Auton_Blue02();
            break;
        case 6:
            // Auton Blue03 Selected
            Brain.Screen.printAt( 60, 125, "Auton Blue03 Selected ");
            Auton_Blue03();
            break;
        case 7:
            // Auton Blue04 Selected
            Brain.Screen.printAt( 60, 125, "Auton Blue04 Selected ");
            Auton_Blue04();
            break;
    }
}
