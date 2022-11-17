/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       LoJac10                                                   */
/*    Created:      Oct 30th, 2022                                            */
/*    Description:  Competition VRC Template for 650X "Xray". Template        */
/*                  includes options to select autonomous programs using      */
/*                  Jpearman 'buttons' & 'autonSelect' module.                */
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

///
// Set Motor Functions
//  - this sets motors between -12000 and 12000.  i'm used to
//  - -100 to 100, so the "scale" variable lets me use that as
//  - inputs and scales it to -12000 to 12000
///

// Set voltage
const int SCALE = 120;


// set drive voltage
void set_drive_pow(int l, int r) {
  LeftFront.spin(fwd, l * SCALE, voltageUnits::mV);
  LeftBack.spin(fwd, l * SCALE, voltageUnits::mV);
  RightFront.spin(fwd, r * SCALE, voltageUnits::mV);
  RightBack.spin(fwd, r * SCALE, voltageUnits::mV);
}

// set tank drive control
void tank_drive(){
  int l_joy = abs(Controller1.Axis3.value()) > 5 ? Controller1.Axis3.value() : 0;
  int r_joy = abs(Controller1.Axis2.value()) > 5 ? Controller1.Axis2.value() : 0;
  set_drive_pow(l_joy, r_joy);
}

// set arcade drive control
void right_arcade_drive(){
  // fwd Axis2 + Axis1
  int l_joy = abs(Controller1.Axis2.value() + Controller1.Axis1.value()) > 5 ? Controller1.Axis2.value() + Controller1.Axis1.value() : 0;
  // turn Axis2 - Axis1
  int r_joy = abs(Controller1.Axis2.value() - Controller1.Axis1.value()) > 5 ? Controller1.Axis2.value() - Controller1.Axis1.value() : 0;
  set_drive_pow(l_joy, r_joy);
}

// set intake voltage
void set_intake(int input) {
  Intake.spin(fwd, input * SCALE, voltageUnits::mV);
}

// set indexer voltage
void set_indexer(int pos, int speed) {
  Indexer.startRotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct);
}

// set flywheel voltage
void set_flywheel(int input) {
  Flywheel1.spin(fwd, input * SCALE, voltageUnits::mV);
  Flywheel2.spin(fwd, input * SCALE, voltageUnits::mV);
}



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
int hex_Red = 0xE00000;     // red HEX color        /* used for Red Autonomous Selection */
int hex_Blue = 0x0000E0;    // blue HEX color       /* used for Blue Autonomous Selection */
int hex_Green = 0x2228c22;  // green HEX color      /* used to indicate most reliable (MONEY) Autonomous Selection */

// Button definitions
button buttons[] = 
{
  {  390,  20, 50, 50,  false, 0xE00000, "RL1" },   // red left Auton Program #1
  {  150,  30, 60, 60,  false, 0xE00000, "RL2" },   // red left Auton Program #2
  {   30, 150, 50, 50,  false, 0xE00000, "RR1" },   // red right Auton Program #1
  {  150, 150, 50, 50,  false, 0xE00000, "RR2" },   // red right Auton Program #2
  {  270, 100, 50, 50,  false, 0x0000E0, "BL1" },   // blue left Auton Program #1
  {  390, 100, 50, 50,  false, 0x0000E0, "BL2" },   // blue left Auton Program #2
  {  270, 180, 50, 50,  false, 0x0000E0, "BR1" },   // blue right Auton Program #1
  {  390, 180, 50, 50,  false, 0x0000E0, "BR2" }    // blue right Auton Program #2
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
   switch( autonomousSelection )
   {
           
    // Red Left 1 Auton Program       
    case 0:
      Auton_RL1();
      break;
           
    // Red Left 2 Auton Program       
    case 1:
      Auton_RL2();
      break;
           
    // Red Right 1 Auton Program       
    case 2:
      Auton_RR1();
      break;
           
    // Red Right 2 Auton Program       
    case 3:
      Auton_RR2();
      break;
    
    // Blue Left 1 Auton Program        
    case 4:
      Auton_BL1();
      break;
   
    // Blue Left 2 Auton Program       
    case 5:
      Auton_BL2();
      break;
    
    // Blue Right 1 Auton Program       
    case 6:
      Auton_BR1();
      break;
    
    // Blue Right 2 Auton Program 
    case 7:
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
int speeds[] = {0, 127, 115, 110, 90};
int speed = 0;
bool indexer_pressed = false;
int target = 0;
int indexer_timer = 0;

void usercontrol(void) {
  Brain.Screen.clearScreen();
    
  int count = 0;
  bool last_r2 = false;
    
  // User control code here, inside the loop
  while ( true ) {
    Brain.Screen.printAt( 60,  125, "Driver Running %5d", count++ );
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // ........................................................................
    /* DRIVE CONTROL SELECTION
       choose drive control here. Uncomment the call to the desired drive 
       control */
    
    // tank drive
    // tank_drive();
      
    // right arcade drive
    right_arcade_drive();

    // ..........................................................................
    

    // intake 
    if (Controller1.ButtonL1.pressing()) {
      set_intake(127); 
    } else if (Controller1.ButtonL2.pressing()) {
      set_intake(-127);
    } else {
      set_intake(0);
    }

    // flywheel
    if (Controller1.ButtonR2.pressing() and !last_r2) {
      if (speed >= 4) {
        speed = 0;
      } else {
        speed++;
      } 
      set_flywheel(speeds[speed]);
    }
    printf("\n %d", speeds[speed]);
    last_r2 = Controller1.ButtonR2.pressing();


    // indexer
    if (Controller1.ButtonR1.pressing()) {

      indexer_pressed = true;
    }
    if (indexer_pressed) {
      if (indexer_timer <= 17) {
        target = 160;
        indexer_timer++;
      } else {
        indexer_timer = 0;
        target = 0;
        indexer_pressed = false;
      }
    }
    
    set_indexer(target, 200);
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

////////////////////////////////////////////////////////////////
//
//    --++| Main |++--
//
//    Main will set up the competition functions and callbacks.
//
//////////////////////////////////////////////////////////////////////////////////////

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
