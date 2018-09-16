/**
 * auton.c - Holds autonomous routines (15 second)
 * borrowed from Brandon
 *
 * @TODO: convert from *.c to *.cpp
 */

void autonMogo() {

}

void autonBlock() {
    
}


string autonRoutines[] = { "Mogo", "Block" };
void goAuton(int routine) {
    switch(routine) {
        default: case 0:
            autonMogo();
            break;
        case 1:
            autonBlock();
            break;
    }
}
