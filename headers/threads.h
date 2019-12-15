/** --- threads.h ---
  * header file to establish thread functions to call from main
  * @TODO: finish thread call for: drive, intake, and traylift
  */

// --- thread call to drive ---
int drive_t(){
  int driveCount = 0; // incrementor
  
  while(true){
   Brain.Screen.printAt( 10, 60, "Task %d", driveCount++);
   
   // don't hog the cpu :)
   vex::this_thread::sleep_for( 25 );
  }
 return( 0 );
}

// --- thread call to trayLift ---

// --- thread call to intake ---
