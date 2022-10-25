/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       operations.h                                              */
/*    Author:       NMS_RP                                                    */
/*    Date:         15 Jan 2020                                               */
/*    Description:  header file for driver operations functions               */
/*                    for Tower Takeover                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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
