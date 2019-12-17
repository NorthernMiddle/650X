using namespace vex;

// VEXcode devices
extern motor LFmotor;
extern motor LBmotor;
extern motor RFmotor;
extern motor RBmotor;
extern motor TLmotor;
extern limit TLlimit;
extern brain Brain;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
