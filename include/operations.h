/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       operations.h                                              */
/*    Author:       LoJac10                                                   */
/*    Date:         Oct 25th, 2022                                            */
/*    Description:  header file for operations functions 650X "Xray"          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/////////////////////////
//
// arcadeDriveRightJoy.h
//
//////////////////////////////////
#ifndef ARCADEDRIVERIGHTJOY_H
#define ARCADEDRIVERIGHTJOY_H

  int cube_drive_l_rightjoy(int drive_l_rightjoy);			 // arcade drive cube scale factor right joystick control
  int cube_drive_r_rightjoyl(int drive_r_rightjoy);			// arcade drive cube scale factor right joystick control
  void deadBand_arcadeRightJoy();
  void arcadeDrive_rightJoy();

#endif


/////////////////////////
//
// flywheel.h
//
//////////////////////////////////
#ifndef FLYWHEEL_H
#define FLYWHEEL_H

  void flywheel_f();

#endif


/////////////////////////
//
// intake.h
//
//////////////////////////////////
#ifndef INTAKE_H
#define INTAKE_H

  void intake_f();

#endif


/////////////////////////
//
// operations.h
//
//////////////////////////////////
#ifndef OPERATIONS_H
#define OPERATIONS_H

  // tank drive
  int deadBand_tankDrive();                         // deadband function for controller
  double ceil_drive_lval( double drive_lval );      // round function to 'whole unit' controller input
  double ceil_drive_rval( double drive_rval );      // round function to 'whole unit' controller input
  double cube_drive_lval( double ceildrive_lval );  // tank drive cube scale factor
  double cube_drive_rval( double ceildrive_rval );  // tank drive cube scale factor  
  int tankDrive_f();                                // tankdrive function call

  // intake (spinners)
  int intake_f();                                   // intake function call

  // tray lift
  void trayLiftSpinUp();                            // spin cubes up
  void trayLiftSpinDown();                          // spin cubes down     
  int trayLift_f();                                 // traylift function call

#endif // OPERATIONS_H
