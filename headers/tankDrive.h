#ifndef TANKDRIVE_H
#define TANKDRIVE_H

int cube_drive_lval(int drive_lval);    // tank drive cube scale factor
int cube_drive_rval(int drive_rval);    // tank drive cube scale factor
void deadBand_Tank();
void tankDrive();


int cube_drive_l_rightjoy(int drive_l_rightjoy);			 // arcade drive cube scale factor right joystick control
int cube_drive_r_rightjoyl(int drive_r_rightjoy);			// arcade drive cube scale factor right joystick control
void deadBand_Arcade();
void arcadeDrive_leftJoy();
void arcadeDrive_rightJoy();

#endif
