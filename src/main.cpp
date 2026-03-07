#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

motor leftDriveA = motor(PORT8, ratio6_1, false);
motor leftDriveB = motor(PORT9, ratio6_1, true); 
motor leftDriveC = motor(PORT10, ratio6_1, true);

motor rightDriveA = motor(PORT12, ratio6_1, true); 
motor rightDriveB = motor(PORT15, ratio6_1, false); //works
motor rightDriveC = motor(PORT3, ratio6_1, false);  //8

inertial Gyro = inertial(PORT18);

controller Controller1 = controller(primary);


motor Main = motor(PORT11, ratio18_1, false);

motor Top = motor(PORT17, ratio6_1, true);

//motor_group Main = motor_group(arm1, arm2);

motor_group LeftDriveSmart = motor_group(leftDriveA, leftDriveB, leftDriveC);
motor_group RightDriveSmart = motor_group(rightDriveA, rightDriveB, rightDriveC);
// smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, Gyro, 3.25*3.1416, 10.5, 9.5, inches, 1.00);

rotation forwad = rotation(PORT16);

//rotation ladybrown = rotation(PORT3, false);
/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
ZERO_TRACKER_ODOM,
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
//ZERO_TRACKER_NO_ODOM,
//TANK_ONE_FORWARD_ROTATION,
//TANK_ONE_SIDEWAYS_ROTATION,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
LeftDriveSmart,

//Right Motors:
RightDriveSmart,

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT20,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1.33,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,


/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
PORT1,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
PORT16,

//Sideways tracker diameter (reverse to make the direction switch):
2,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected  by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  //Gyro.calibrate();
  //chassis.calibrate();               // (blocks until IMU is ready in most JAR builds)
  chassis.set_coordinates(0, 0, 0);


  // while(!auto_started){
  //   Brain.Screen.clearScreen();
  //   Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
  //   Brain.Screen.printAt(5, 40, "Battery Percentage:");
  //   Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
  //   Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
  //   Brain.Screen.printAt(5, 100, "%f", chassis.get_absolute_heading());
  //   Brain.Screen.printAt(5, 120, "Selected Auton:");
  //   switch(current_auton_selection){
  //     case 0:
  //       Brain.Screen.printAt(5, 140, "Auton 1");
  //       break;
  //     case 1:
  //       Brain.Screen.printAt(5, 140, "Auton 2");
  //       break;
  //     case 2:
  //       Brain.Screen.printAt(5, 140, "Auton 3");
  //       break;
  //     case 3:
  //       Brain.Screen.printAt(5, 140, "Auton 4");
  //       break;
  //     case 4:
  //       Brain.Screen.printAt(5, 140, "Auton 5");
  //       break;
  //     case 5:
  //       Brain.Screen.printAt(5, 140, "Auton 6");
  //       break;
  //     case 6:
  //       Brain.Screen.printAt(5, 140, "Auton 7");
  //       break;
  //     case 7:
  //       Brain.Screen.printAt(5, 140, "Auton 8");
  //       break;
  //   }
  //   if(Brain.Screen.pressing()){
  //     while(Brain.Screen.pressing()) {}
  //     current_auton_selection ++;
  //   } else if (current_auton_selection == 8){
  //     current_auton_selection = 0;
  //   }
  //   task::sleep(10);
  // }
}

/**
 * Auton function, which runs th be selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

 void IntakeStop()
{
    
        Main.stop();
        Top.stop();
        
        


} 
void Intake()
{
    
        Main. spin(fwd, 50, pct);
        //Top.spin(fwd, 100, pct);
        
        


}
void IntakeTop()
{

      Main.spin(fwd, 100, pct);
      Top.spin(fwd, 100, pct);
 
}

void Unjam()
{
      Top.spin(reverse, 75, pct);
      Main.spin(reverse, 75, pct);
}
void SevenBall_Right()
{
  chassis.drive_max_voltage = 12;
  Intake();
  chassis.set_drive_exit_conditions(1, 75, 1200);
  chassis.drive_distance(52);
  chassis.set_turn_exit_conditions(5, 75, 1200);
  chassis.turn_to_angle(28);
  chassis.set_drive_exit_conditions(1, 100, 300);
  chassis.drive_distance(4);
  Insertpiston.set(true);
  chassis.set_drive_exit_conditions(1, 100, 1200);
  chassis.drive_distance(19);
  chassis.set_turn_exit_conditions(1, 200, 1200);
  chassis.turn_to_angle(125);
  IntakeStop();
  chassis.set_drive_exit_conditions(1.5, 200, 1200);
  chassis.drive_distance(63);
  chassis.set_turn_exit_conditions(2, 200, 1200);
  chassis.turn_to_angle(180);
  chassis.set_drive_exit_conditions(2, 400, 800);
  Intake();
  chassis.drive_distance(24);
  chassis.set_turn_exit_conditions(3, 200, 2000);
  chassis.turn_to_angle(180);
  chassis.set_drive_exit_conditions(10, 300, 1200);
  chassis.drive_distance(-63);
  
  IntakeTop();
  wait(0.2, sec); 

  Unjam();
  wait(0.3, sec);
  IntakeTop();
  wait(2, sec);


}

void SevenBall_Left()
{
  chassis.drive_max_voltage = 12;
  Intake();
  chassis.set_drive_exit_conditions(1, 75, 1200);
  chassis.drive_distance(50);
  chassis.set_turn_exit_conditions(5, 75, 1200);
  chassis.turn_to_angle(335);
  Insertpiston.set(true);
  chassis.set_drive_exit_conditions(1, 100, 1200);
  chassis.drive_distance(15);
   //Collects first 3 balls
  chassis.set_turn_exit_conditions(1, 200, 1200);
  chassis.turn_to_angle(-130);
  
  IntakeStop();
  chassis.set_drive_exit_conditions(1.5, 200, 1200);
  chassis.drive_distance(58);
  chassis.set_turn_exit_conditions(2, 200, 1200);
  chassis.turn_to_angle(-176);
  chassis.set_drive_exit_conditions(2, 220, 800);
  Intake();
  chassis.drive_distance(22);
  
  // wait(0.4, sec);
  chassis.set_turn_exit_conditions(3, 150, 1200);
  chassis.turn_to_angle(180);
  chassis.set_drive_exit_conditions(8, 300, 1200);
  chassis.drive_distance(-63);

  IntakeTop();
  wait(0.2, sec); 

  Unjam();
  wait(0.3, sec);
  IntakeTop();
  wait(2, sec);

  chassis.set_drive_exit_conditions(1, 50, 1200);
  IntakeStop();
  chassis.drive_distance(8);
  chassis.set_turn_exit_conditions(10, 25, 1200);
  chassis.turn_to_angle(90);
  chassis.set_drive_exit_conditions(1, 150, 325);
  chassis.drive_distance(-17.75);
  chassis.set_turn_exit_conditions(20, 25, 300);
  chassis.turn_to_angle(177); // CHANGE THIS
  chassis.set_drive_exit_conditions(4, 300, 1000);
  chassis.drive_distance(-46, 180, 7, 7);
  chassis.set_drive_exit_conditions(0, 1000, 1200);
  chassis.drive_distance(1, 180, 12, 12);

  // IntakeTop();
  // // IntakeTop();
  // // wait(1, sec);
  // Intake();
  // chassis.drive_distance(15, 180, 12, 4, 1200, 1200, 1200);


  // chassis.turn_to_angle(355, 12);
  // chassis.drive_distance(33, 180, 10, 4);
  // Insertpiston.set(true);
  // wait(0.5, sec);
  // Intake();
  // chassis.drive_distance(15, 180, 12, 4);
  // wait(0.25, sec);
  // IntakeStop();
  // chassis.drive_distance(-70, 185, 10, 4, 1000, 1000, 1000);
  // wait(0.5, sec);
  // IntakeTop();
  // wait(3, sec);
  // IntakeStop();

  
}

void Fourpushleft()
{

  chassis.drive_distance(50, 0, 11, 8);
  chassis.turn_to_angle(335, 8);
  Intake();
  chassis.drive_distance(4, 338, 12, 4);
  Insertpiston.set(true);
  chassis.drive_distance(20, 338, 12, 4);
  wait(0.5, sec);
  chassis.turn_to_angle(225, 8);

  IntakeStop();
  
  Insertpiston.set(false);
  chassis.drive_distance(67, 225, 10, 4);
  chassis.turn_to_angle(177, 8);
  chassis.drive_distance(-40, 180, 10, 4);
  IntakeTop();
  wait(1, sec);
  
  chassis.drive_distance(12, 180, 12, 4);
  //chassis.turn_to_angle(355, 12);
  chassis.turn_to_angle(90, 10);
  chassis.turn_to_angle(180, 10);
  chassis.drive_distance(-42, 180, 8, 8);






 
 




  
}

void limited() 
{
  chassis.drive_distance(4, 0);
} 
void autonomous(void) {
  SevenBall_Right();
  //SevenBall_Left();
  
  //limited();
  
}

bool middleBool = false;
bool insertBool = false;
void usercontrol(void) {
  // User control code here, inside the loop
  chassis.set_coordinates(0, 0, 0);
  //bool buttonvalue = 0;
  //ladybrown.resetPosition();
  //Controller1.ButtonDown.pressed( []() {armTargetPosition = -70; });
  //Controller1.ButtonR1.pressed( []() {armTargetPosition = 90; });
  // User control code here, inside the loop
  //bool DrivetrainLNeedsToBeStopped_Controller1 = true;
  //bool DrivetrainRNeedsToBeStopped_Controller1 = true;


  //bool Hang_toggle = false;

  //vex::task LBControl(setLB);

  //Piston stuff
 // bool Middlepiston_Toggle = false; 
 // bool InsertPiston_Toggle = false; 
 // bool AlternatePiston_Toggle = false;

   
 // bool lastButtonAPressed = false;   // track previous button state

while (1) {
  
  
 // bool currentButtonAPressed = Controller1.ButtonA.pressing();
 
  if (Controller1.ButtonA.pressing()) {
    insertBool = !insertBool;
    waitUntil(!Controller1.ButtonA.pressing());
  }
  Insertpiston.set(insertBool);
  
  if (Controller1.ButtonDown.pressing()){
    middleBool = !middleBool;
    waitUntil(!Controller1.ButtonDown.pressing());
  }
  Middlepiston.set(middleBool);

    //lastButtonAPressed = currentButtonAPressed;      
    //Brain.Screen.print("%f, %f", chassis.get_X_position(),chassis.get_Y_position());
   
  //Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  //chassis.set_coordinates(0, 0, 0);
  Brain.Screen.print("%f, %f", chassis.get_X_position(),chassis.get_Y_position());
   
  //Brain.Screen.print("%f", ladybrown.position(degrees));
  /*
  if(Controller1.ButtonUp.pressing())
  {
    Insertpiston.set(true);
  }
  else
  {
    Insertpiston.set(false);
  }

  if(Controller1.ButtonDown.pressing())
  {
    Alternatepiston.set(true);
  }
  else
  {
    Alternatepiston.set(false);
  }
    */
  
  if(Controller1.ButtonR1.pressing() && Controller1.ButtonR2.pressing())
   {
     
      
           Main. spin(fwd, 100, pct);
          Top.spin(fwd, 100, pct);
   }
    else if(Controller1.ButtonL1.pressing())  //TOP
      {
      //Alternatepiston.set(false);
     
      Main. spin(fwd, 100, pct);
        Top.spin(fwd, 100, pct);
    
      LeftDriveSmart.stop(brake);
      RightDriveSmart.stop(brake);
      // Drivetrain.stop(brake);
      
      

      

        // setpos = false;
      }
    
    else if(Controller1.ButtonR2.pressing()) //Outake out of robot down
      {
        //Alternatepiston.set(true);
     
        Main. spin(reverse, 50, pct);
        Top.spin(fwd, 15, pct);
    

        // setpos = false;
      }
      else if(Controller1.ButtonR1.pressing()) //Intake into robot
      {
       
      
       //Back.spin(reverse, 100, pct);
     
      Main.spin(fwd, 95, pct);
      //Top.spin(reverse, 5, pct);
      }
      else if(Controller1.ButtonL2.pressing()) //MIDDLE GOAL
      {
        
        if (Controller1.ButtonL2.pressing()) {
        Alternatepiston.set(!Alternatepiston.value());
          wait(100, msec);
        }
  }

  
  
      

        // setpos = false;
       else
      {
     
        Main.stop(coast);
     
       Top.stop(hold);
      wait(20, msec);
      LeftDriveSmart.stop(coast);
      RightDriveSmart.stop(coast);
      // Drivetrain.stop(coast);
      }
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();
//     int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
// int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();

// LeftDriveSmart.spin(forward, drivetrainLeftSideSpeed , percent);
// RightDriveSmart.spin(forward, drivetrainRightSideSpeed , percent);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
