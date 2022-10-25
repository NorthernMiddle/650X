/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       LoJac10                                                   */
/*    Created:      10/25/2022                                                */
/*    Description:  Competition VRC Template for 650X "Xray". Template        */
/*                  includes options to select autonomous programs using      */
/*                  Jpearman 'buttons' module.                                */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller      
// TrayLiftlimit        limit         A                     
// LFmotor              motor         1
// LBmotor              motor         2
// RFmotor              motor         3
// RBmotor              motor         4   
// TrayLiftmotor        motor         8               
// L_Intake             motor         9               
// R_Intake             motor         10           
// Drivetrain           drivetrain    1, 2, 3, 4      
// ---- END VEXCODE CONFIGURED DEVICES ----

// VEX V5 C++ Project
#include "vex.h"
#include "auton.h"
#include "operations.h"
#include "fieldgraphic.h"
using namespace vex;

// A global instance of competition
competition Competition;

int autonomousSelection = -1;

// collect data for on screen button
typedef struct _button 
{
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color color;
    const char *label;
} button;

// Button definitions
button buttons[] = 
{
  {   390,  20, 50, 50,  false, 0x228c22, "Straight" },
  //{  150,  30, 60, 60,  false, 0xE00000, "RL" },
  //{   30, 150, 50, 50,  false, 0xE00000, "RL" },
  //{  150, 150, 50, 50,  false, 0xE00000, "RR" },
  {  270, 100, 50, 50,  false, 0xE00000, "RL" },
  {  390, 100, 50, 50,  false, 0xE00000, "RR" },
  {  270, 180, 50, 50,  false, 0x0000E0, "BL" },
  {  390, 180, 50, 50,  false, 0x0000E0, "BR" }
};

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int findButton(  int16_t xpos, int16_t ypos ) 
{
  int nButtons = sizeof(buttons) / sizeof(button);

  for( int index=0; index < nButtons; index++) 
  {
    button *pButton = &buttons[ index ];
    if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
      continue;

    if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
      continue;
    
    return(index);
  }
  return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void initButtons() 
{
  int nButtons = sizeof(buttons) / sizeof(button);

  for( int index=0; index < nButtons; index++) 
  {
    buttons[index].state = false;
  }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void displayButtonControls( int index, bool pressed ) 
{
  color c;
  Brain.Screen.setPenColor( color( white ) );    // used to outline buttons and write labels

  for( int i=0; i<sizeof(buttons)/sizeof(button); i++ ) 
  {
    
    if( buttons[i].state )
      c = buttons[i].color;
    else
      c = vex::color::black;

    Brain.Screen.setFillColor( c );

    // button fill
    if( i == index && pressed == true ) 
    {
      c = c + 0x404040; /* colors button from black (unselected) to gray (transition color) 
      for sec after touch until selection color is loaded into button after selection */
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
    }
    else
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

    // outline
    Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, color::transparent );

    // draw label
    if(  buttons[i].label != NULL )
      Brain.Screen.printAt( buttons[i].xpos + 5, buttons[i].ypos + buttons[i].height - 5, buttons[i].label );
  }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackPressed()
{
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  
  if( (index = findButton( xpos, ypos )) >= 0 ) 
  {
    displayButtonControls( index, true );
  }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackReleased() 
{
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  
  if( (index = findButton( xpos, ypos )) >= 0 ) 
  {
    // clear all buttons to false, ie. unselected
    initButtons();

    // now set this one as true
    buttons[index].state = true;
    
    // save as auton selection
    autonomousSelection = index;
    
    displayButtonControls( index, false );
  }
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  int count = 0;
  while( true )
  {
    if( autonomousSelection < 0 )
      Brain.Screen.printAt( 60,  125, "Auton not selected  " );
    else
      Brain.Screen.printAt( 60,  125, "Auton %d Running %5d", autonomousSelection, count++ );
   switch( autonomousSelection )
   {
    case 0:
      // RL1 Auton Program
      Auton_Straight();
      break;
    case 1:
      // RL2 Auton Program
      Auton_RL();
      break;
    case 2:
      // RR2 Auton Program
      Auton_RR();
      break;
    case 3:
      // BL1 Auton Program
      Auton_BL();
      break;
    case 4:
      // BR1 Auton Program
      Auton_BR();
      break;
    }
    break;
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  Brain.Screen.clearScreen();
  int count = 0;
  while ( true ) {
    Brain.Screen.printAt( 60,  125, "Driver Running %5d", count++ );
    thread tankdrive_t = thread(tankDrive_f);     // thread DRIVE
    thread lift_t = thread(trayLift_f);           // thread TRAY LIFT
    thread spinners_t = thread(intake_f);         // thread INTAKE
    task::sleep(100); 
  }
}

/////////////////////////////////////////////////////////////////////
//
//      +++++++++++++++++++ MAIN +++++++++++++++++++
//
/////////////////////////////////////////////////////////////////////
int main() {
  
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    // register events
    Brain.Screen.pressed( userTouchCallbackPressed );
    Brain.Screen.released( userTouchCallbackReleased );
    
    // background
    Brain.Screen.setFillColor( vex::color(kLedColorWhite) );
    Brain.Screen.drawRectangle( 0, 0, 240, 240);

    fieldGraphic();

    Brain.Screen.setFillColor( vex::color(0x404040) );
    Brain.Screen.setPenColor( vex::color(0x404040) );
    Brain.Screen.drawRectangle( 240, 0, 240, 165 );

    Brain.Screen.setFillColor( vex::color(kLedColorRed) );
    Brain.Screen.setPenColor( vex::color(kLedColorRed) );
    Brain.Screen.drawRectangle( 240, 85, 240, 170 );

    Brain.Screen.setFillColor( vex::color(kLedColorBlue) );
    Brain.Screen.setPenColor( vex::color(kLedColorBlue) );
    Brain.Screen.drawRectangle( 240, 165, 240, 240 );

    // initial display
    displayButtonControls( 0, false );
    
    while( true ) {
      // Allow other tasks to run
      if( !Competition.isEnabled() )
        Brain.Screen.printAt( 60,  90, "Disabled. Make Auton Selection.        " );
      this_thread::sleep_for(10);
    }
}
