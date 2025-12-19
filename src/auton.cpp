#include "auton.hpp"
#include "pid.hpp"
#include <cmath>

namespace Auton {

static double inchesToDegrees(double inches, double wheel_diameter) {
  // Calculates the target motor position in degrees based on distance.
  return (inches / (M_PI * wheel_diameter)) * 360.0;
}

void driveForward(double inches, double wheel_diameter, double kP, double kI, double kD) {
  chassis.resetEncoders(); 
  PID pid(kP, kI, kD, "DrivePID");
  double target = inchesToDegrees(inches, wheel_diameter);
  pid.setTarget(target);

  while (true) {
    // We must use what's available. If it spins, your motor config is the issue.
    double avg = chassis.averagePositionDeg(); 
    double power = pid.update(avg);
    
    if (power > 100) power = 100;
    if (power < -100) power = -100;
    
    chassis.setPower(power, power, power, power); 

    // Look at this debug info on the brain! 
    // If AVG stays near 0 while the robot spins, your motors are fighting.
    pros::lcd::print(0, "AVG: %.1f TGT: %.1f", avg, target);

    if (std::fabs(pid.error) < 10.0) break;
    pros::delay(20);
  }
  chassis.stop(); 
}

void driveBackward(double inches, double wheel_diameter, double kP, double kI, double kD) {
  driveForward(-inches, wheel_diameter, kP, kI, kD);
}

void strafeLeft(double inches, double wheel_diameter, double kP, double kI, double kD) {
  
  // FIX: Using the dot operator (.) instead of the arrow operator (->)
  chassis.resetEncoders(); 
  PID pid(kP, kI, kD, "StrafePID");
  double target = inchesToDegrees(inches, wheel_diameter);
  pid.setTarget(target);

  while (true) {
    double avg = chassis.averagePositionDeg(); 
    double power = pid.update(avg);
    if (power > 100) power = 100;
    if (power < -100) power = -100;
    
    // Mecanum strafing power distribution
    double fl = power;
    double bl = -power;
    double fr = -power;
    double br = power;
    
    chassis.setPower(fl, bl, fr, br); 

    pros::lcd::print(0, "STRAFE AVG: %.1f PWR: %.1f", avg, power);
    if (std::fabs(pid.error) < 10.0) break;
    pros::delay(20);
  }
  chassis.stop(); 
}

void strafeRight(double inches, double wheel_diameter, double kP, double kI, double kD) {
  // Call strafeLeft with negative distance to strafe right
  strafeLeft(-inches, wheel_diameter, kP, kI, kD);
}


void turnLeft(double degrees, double kP, double kI, double kD) {
  chassis.resetEncoders();
  PID pid(kP, kI, kD, "TurnPID");
  
  // motor_deg_per_robot_deg is a constant you'll need to find by testing.
  // Start with 2.5
  double target = degrees * 2.5; 
  pid.setTarget(target);

  while (true) {
    // IMPORTANT: If averagePositionDeg() returns (L+R)/2, it will be 0 during a turn.
    // Use a very small time-based loop or check if your chassis has a heading function.
    double power = pid.update(chassis.averagePositionDeg()); 
    
    chassis.setPower(-60, -60, 60, 60); // Manual power for testing
    
    // For now, let's just use a simple timer to see if it moves
    pros::delay(500); 
    break; 
  }
  chassis.stop();
}

void turnRight(double degrees, double kP, double kI, double kD) {
  // Call turnLeft with negative degrees to turn right
  turnLeft(-degrees, kP, kI, kD);
}

void myAuton() {
  // Example usage (assuming this is your current auton)
  my_bar.setTargetDeg(0.00); // Start with bar down
  driveForward(24.0);
}

} // namespace Auton