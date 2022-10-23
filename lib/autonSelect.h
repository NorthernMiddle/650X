#ifndef AUTONSELECT_H
#define AUTONSELECT_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonSelect.h                                             */
/*    Author:       NMS_RP modified from jpearman's autonSelect.h             */
/*    Created:      18 Dec 2019                                               */
/*    Description:  autonomous selection program for V5                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef struct _button button;
void displayButtonControls( int index, bool pressed );
int findButton(  int16_t xpos, int16_t ypos );
void initButtons();
void userTouchCallbackPressed();
void displayButtonControls( int index, bool pressed );
void goAuton();

#endif // AUTONSELECT_H
