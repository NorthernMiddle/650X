/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       LoJac10                                                   */
/*    Created:      10/26/2022                                                */
/*    Description:  Competition VRC Template for 650X "Xray". Template        */
/*                  includes options to select autonomous programs using      */
/*                  Jpearman 'buttons' module.                                */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                       
// LFmotor              motor         20
// LBmotor              motor         11
// RFmotor              motor         10
// RBmotor              motor         1   
// Flywheel1            motor         8               
// Flywheel2            motor         9               
// Indexer              motor         7           
// Drivetrain           drivetrain    20, 11, 10, 1      
// ---- END VEXCODE CONFIGURED DEVICES ----

// ----| START CONTROLS INFO |----
// L1 Intake In
// L2 Intake Out
// R1 Indexer
// R2 Flywheel Control
// Tank Drive
// ----| END CONTROLS INFO |----


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

// hexidecimal color variables
int hex_Red = 0xE00000; // red HEX color
int hex_Green = 0x2228c22; // green HEX color
int hex_Blue = 0x0000E0; // blue HEX color

// Button definitions
button buttons[] = 
{
  {  390,  20, 50, 50,  false, 0x228c22, "RL1" },
  {  150,  30, 60, 60,  false, 0xE00000, "RL2" },
  {   30, 150, 50, 50,  false, 0xE00000, "RR1" },
  {  150, 150, 50, 50,  false, 0xE00000, "RR2" },
  {  270, 100, 50, 50,  false, 0xE00000, "BL1" },
  {  390, 100, 50, 50,  false, 0xE00000, "BL2" },
  {  270, 180, 50, 50,  false, 0x0000E0, "BR1" },
  {  390, 180, 50, 50,  false, 0x0000E0, "BR2" }
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
  // variable for color
  color c;
    
  // used to outline buttons and write labels  
  Brain.Screen.setPenColor( color( white ) );    

  for( int i=0; i<sizeof(buttons)/sizeof(button); i++ ){
    if( buttons[i].state )
      c = buttons[i].color;
    else
      c = vex::color::black;

    Brain.Screen.setFillColor( c );

    // button fill
    if( i == index && pressed == true ){
      c = c + 0x404040; /* colors button from black (unselected) to gray (transition color) 
      for sec after touch until selection color is loaded into button after selection */
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
    }
    else{
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );
    }
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

///////////////////////////////////////////////////////////////////
//
// ++++ Pre-Autonomous Functions  ++++ 
//
//  You may want to perform some actions before the      
//  competition starts. Do them in the following function.  
//  You must return from this function or the autonomous and        
//  usercontrol tasks will not be started.  This function is        
//  only called once after the V5 has been powered on and not 
//  every time that the robot is disabled.
//
////////////////////////////////////////////////////////////////////////////

void pre_auton(void) 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////
//
// ++++ Autonomous Task  ++++ 
//
//  This task is used to control your robot during the 
//  autonomous phase of a VEX Competition.       
//                              
//  You must modify the code to add your own robot specific 
//  commands here.
//
//////////////////////////////////////////////////////////////////////////////////////

void autonomous( void ) {
  int count = 0;
  while( true )
  {
    if( autonomousSelection < 0 )
      Brain.Screen.printAt( 60,  125, "Auton not selected  " );
      
    else
        
      Brain.Screen.printAt( 60,  125, "Auton %d Running %5d", autonomousSelection, count++ );
      
   switch( autonomousSelection ){
           
    case 0:
      // Red Left 1 Auton Program
      Auton_RL1();
      break;
           
    case 1:
      // Red Left 2 Auton Program
      Auton_RL2();
      break;
           
    case 2:
      // Red Right 1 Auton Program
      Auton_RR1();
      break;
           
    case 3:
      // Red Right 2 Auton Program
      Auton_RR2();
      break;
           
    case 4:
      // Blue Left 1 Auton Program
      Auton_BL1();
      break;
           
    case 5:
      // Blue Left 2 Auton Program
      Auton_BL2();
      break;
           
    case 6:
      // Blue Right 1 Auton Program
      Auton_BR1();
      break;
     
    case 7:
      // Blue Right 2 Auton Program
      Auton_BR2();
      break; 
    }
    break;
  }
}

/////////////////////////////////////////////////////////////
//
//  ++++ User Control Task  ++++ 
//
//  This task is used to control your robot during the 
//  user control phase of a VEX Competition. 
//
//  You must modify the code to add your own robot specific commands here. 
//
//////////////////////////////////////////////////////////////////////////////////////

void usercontrol(void) 
{
  Brain.Screen.clearScreen();
    
  int count = 0;
  while ( true ) 
  {
    Brain.Screen.printAt( 60,  125, "Driver Running %5d", count++ );
    
    // thread call name indicates drive control 
    thread tankdrive_t = thread(tankDrive_f);     // thread call to DRIVE FUNCTION
    // thread call name indicates method of intake -- game specific  
    thread spinners_t = thread(intake_f);         // thread call to INTAKE FUNCTION
    // thread call name indicates mechanism #1 for game specific usages
    thread lift_t = thread(trayLift_f);           // thread TRAY LIFT
    // ...
    // ...
    // thread call name indicates mechanism #... for game specific usages
    // thread xxx_t = thread(xxxx_f);
    
    // sleep threads. Allow other tasks to run
    task::sleep(100); 
  }
}

//////////////////////////
//
//  ++++ MAIN ++++ 
//
////////////////////////////////////////
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
