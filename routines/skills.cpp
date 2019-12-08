/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       skills.h                                                  */
/*    Author:       NMS_RP                                                    */
/*    Created:      23 Nov 2019                                               */
/*    Description:  60 Second Skills Routines                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/



/**	skillsRed.h
  *	
  *
  */
void skillsRed() {
  // enter your Red Alliance skills program here...
}

/**	skillsBlue.h
  *	
  *
  */
void skillsBlue() {
  // enter your Blue Alliance skills program here...
}

//////////////////////////////////////
//
//	--- Skills Routine Selector ---
//
//////////////////////////////////////

std::string skillsRoutines[] = { "Red, Blue" };
void goSkills(int routine) {
    switch(routine) {
        default: case 0:
			// Red Skills Routine Selected
			Brain.Screen.printAt( 60, 125, "Red Skills Routine Selected ");
            skillsRed();
            break;
		case 1:
			// Blue Skills Routine Selected
			Brain.Screen.printAt( 60, 125, "Blue Skills Routine Selected ");
            skillsBlue();
            break;
    }
}
