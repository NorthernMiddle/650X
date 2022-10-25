/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonSelect.h                                             */
/*    Author:       NMS_RP modified from jpearman's autonSelect.h             */
/*    Created:      18 Dec 2019                                               */
/*    Description:  autonomous selection program for V5                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef AUTONSELECT_H
#define AUTONSELECT_H

  typedef struct _button button;
  void displayButtonControls( int index, bool pressed );
  int findButton(  int16_t xpos, int16_t ypos );
  void initButtons();
  void userTouchCallbackPressed();
  void displayButtonControls( int index, bool pressed );
  void goAuton();

#endif // AUTONSELECT_H



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.h                                                   */
/*    Author:       NMS_RP                                                    */
/*    Created:      18 Dec 2019                                               */
/*    Description:  autonomous program file holder header file                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef AUTON_H
#define AUTON_H

  void Auton_Straight();

  void Auton_RL();
  void Auton_RR();

  void Auton_BL();
  void Auton_BR();

  void goAuton();

#endif // AUTON_H
