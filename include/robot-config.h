using namespace vex;

// brain
extern brain Brain;

// controller
extern controller Controller1;

// sensors
extern inertial DrivetrainInertial;

// motors
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;
extern motor Indexer;
extern motor Intake;
extern motor Flywheel1;
extern motor Flywheel2;

// motor groups
extern motor_group Flywheel;
extern motor_group LeftSide;
extern motor_group RightSide;

// drivetrain
extern smartdrive robotDrive;



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

