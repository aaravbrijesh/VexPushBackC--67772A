// src/robot.cpp

// Include the general PROS header and your subsystem headers
#include "main.h" 
#include "robot.hpp" // Keep this if it contains declarations for the Robot namespace
#include "drive.hpp" // Necessary for MecanumDrive class definition
#include "intake.hpp"
#include "outtake.hpp"
#include "bar.hpp"
#include "treads.hpp"


// ----------------------------------------------------------------------
// 1. HARDWARE DEFINITIONS (Global Motors & Controller)
// These PROS Motor objects and the Controller are defined outside the 
// namespace, matching the extern declarations in main.h.
// ----------------------------------------------------------------------

// Controller Definition (MUST be global)
pros::Controller controller(CONTROLLER_MASTER); // Renamed 'master' to 'controller' for consistency

// Left Drive
pros::Motor front_left(PORT_FL, pros::MotorGears::green);
pros::Motor back_left(PORT_BL, pros::MotorGears::green);

// Right Drive (Negative port for reversing)
pros::Motor front_right(-PORT_FR, pros::MotorGears::green);
pros::Motor back_right(-PORT_BR, pros::MotorGears::green);

// Subsystems
pros::Motor intake_motor(PORT_INTAKE, pros::MotorGears::green);
pros::Motor outtake_motor(PORT_OUTTAKE, pros::MotorGears::green);
pros::Motor bar_motor(PORT_BAR, pros::MotorGears::green);
pros::Motor treads_motor(PORT_TREADS, pros::MotorGears::green);


// ----------------------------------------------------------------------
// 2. SUBSYSTEM INSTANCES (Global Custom Class Objects)
// These custom objects are defined globally, matching externs in main.h.
// ----------------------------------------------------------------------

// The Mecanum chassis object
MecanumDrive chassis(front_left, back_left, front_right, back_right);

// The other subsystem objects
Intake my_intake(intake_motor);
Outtake my_outtake(outtake_motor);
Bar my_bar(bar_motor);
Treads my_treads(treads_motor);


namespace Robot {

// ----------------------------------------------------------------------
// 3. INITIALIZATION FUNCTION
// ----------------------------------------------------------------------

void init() {
  // Reset encoders using the global object
  chassis.resetEncoders();
  
  // FIX: Replaced my_bar.resetEncoders() with the correct PROS function 
  // on the motor object itself.
  bar_motor.tare_position(); 
  
  // Note: Your original code had 'bar_motor.tare_position();' at the end of the init() 
  // function in an earlier version, so we restore the correct method here.
}

// You can delete the shutdown() function as PROS handles cleanup of globally defined objects. 

// The rest of your Robot namespace functions go here...

} // namespace Robot