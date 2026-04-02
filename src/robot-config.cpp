#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Piston stuff
digital_out Middlepiston = digital_out(Brain.ThreeWirePort.G); //Change the port
digital_out Insertpiston = digital_out(Brain.ThreeWirePort.D);
digital_out Alternatepiston = digital_out(Brain.ThreeWirePort.B);
digital_out MidDescorepiston = digital_out(Brain.ThreeWirePort.H);
//digital_out UpDownpiston = digital_out(Brain.ThreeWirePort.E);
//digital_out ColorSort = digital_out(Brain.ThreeWirePort.C);

// VEXcode generated functions
//Add your devices below, and don't forget to do the same in robot-config.h:


void vexcodeInit( void ) {
  // nothing to initialize
}