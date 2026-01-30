// src/robot.cpp

// Include the general PROS header and your subsystem headers
#include "main.h" 
#include "robot.hpp" // Includes the Robot namespace definition.
#include "drive.hpp" 
#include "intake.hpp"
#include "outtake.hpp"
#include "bar.hpp"

// ----------------------------------------------------------------------
// 1. HARDWARE DEFINITIONS (Global Motors & Controller)
// Global hardware definitions for PROS Motor objects and the Controller.
// ----------------------------------------------------------------------

// Controller object definition.
pros::Controller controller(CONTROLLER_MASTER); 

// Left Drive
pros::Motor front_left(PORT_FL, pros::MotorGears::green);
pros::Motor back_left(PORT_BL, pros::MotorGears::green);

// Right Drive (Port set to negative for physical direction reversal)
pros::Motor front_right(-PORT_FR, pros::MotorGears::green);
pros::Motor back_right(-PORT_BR, pros::MotorGears::green);

// Subsystems
pros::Motor intake_motor(PORT_INTAKE, pros::MotorGears::green);
pros::Motor long_outtake_motor(PORT_LONG_OUTTAKE, pros::MotorGears::green);
pros::Motor upper_outtake_motor(PORT_UPPER_OUTTAKE, pros::MotorGears::green);
pros::Motor bar_motor(PORT_BAR, pros::MotorGears::green);

// ----------------------------------------------------------------------
// 2. SUBSYSTEM INSTANCES (Global Custom Class Objects)
// These custom objects are defined globally, matching externs in main.h.
// ----------------------------------------------------------------------

// The Mecanum chassis object
MecanumDrive chassis(front_left, back_left, front_right, back_right);

// The other subsystem objects
Intake my_intake(intake_motor);
Outtake long_outtake(long_outtake_motor);
Outtake upper_outtake(upper_outtake_motor);
Bar my_bar(bar_motor);

namespace Robot {

// ----------------------------------------------------------------------
// 3. INITIALIZATION FUNCTION
// ----------------------------------------------------------------------

void init() {
  // Reset drive encoders using the global object.
  chassis.resetEncoders();
  
  // Sets the bar motor's current position to zero degrees.
  bar_motor.tare_position(); 
  
  // NOTE: Outtakes are already constructed as objects globally
  // No need to use 'new' here
}

} // namespace Robot
