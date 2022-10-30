/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.h                                                   */
/*    Author:       LoJac10                                                   */
/*    Created:      Oct 30th, 2022                                            */
/*    Description:  auton program select module and auton program             */
/*    header file                                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

  // module: autonSelect.h
  // author: jpearman's autonSelect.h
  typedef struct _button button;
  void displayButtonControls( int index, bool pressed );
  int findButton(  int16_t xpos, int16_t ypos );
  void initButtons();
  void userTouchCallbackPressed();
  void displayButtonControls( int index, bool pressed );

  // module: auton programs
  void Auton_RL1();
  void Auton_RL2();
  void Auton_RR1();
  void Auton_RR2();
  void Auton_BL1();
  void Auton_BL2();
  void Auton_BR1();
  void Auton_BR2();
