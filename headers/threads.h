/** --- threads.h ---
  *
  * header file to establish thread functions to call from main
  *
  */

///////////////////////////////////////////////////////////////////
//
// --- thread call to drive ---
//
///////////////////////////////////////////////////////////////////
int drive_t(){
  int driveCount = 0; // incrementor
  
  while(true){
   Brain.Screen.printAt( 10, 60, "Task %d", driveCount++);
   
   // don't hog the cpu :)
   vex::this_thread::sleep_for( 25 );
  }
 return( 0 );
}

///////////////////////////////////////////////////////////////////
//
// --- thread call to trayLift ---
//
///////////////////////////////////////////////////////////////////
int trayLift_t(){
 int trayLiftCount = 0; // incrementor
 
 while(true){
  Brain.Screen.printAt( 10, 60, "Task %d", trayLiftCount++);
  
  // don't hog the cpu :)
   vex::this_thread::sleep_for( 25 );
  }
 return( 0 );
}

///////////////////////////////////////////////////////////////////
//
// --- thread call to intake ---
//
///////////////////////////////////////////////////////////////////
int intake_t(){
 int intakeCount = 0;
 
 while(true){
  Brain.Screen.printAt( 10, 60, "Task %d", intakeCount++);
  
   // don't hog the cpu :)
   vex::this_thread::sleep_for( 25 );
  }
 return( 0 );
}
