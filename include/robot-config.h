using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:
// extern limit triballsensor;
extern digital_out Color;
extern digital_out Alternatepiston;
extern digital_out Insertpiston;

//Piston stuff
extern digital_out Examplepiston; 



void  vexcodeInit( void );