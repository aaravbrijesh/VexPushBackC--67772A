#include "auton.hpp"
#include "pid.hpp"
#include <cmath>

namespace Auton {

static double inchesToDegrees(double inches, double wheel_diameter) {
  // Calculates the target motor position in degrees based on distance.
  return (inches / (M_PI * wheel_diameter)) * 360.0;
}

void driveForward(double inches, double wheel_diameter, double kP, double kI, double kD) {
  // FIX: Using the dot operator (.) instead of the arrow operator (->)
  chassis.resetEncoders(); 
  PID pid(kP, kI, kD, "DrivePID");
  double target = inchesToDegrees(inches, wheel_diameter);
  pid.setTarget(target);

  while (true) {
    double avg = chassis.averagePositionDeg(); 
    double power = pid.update(avg);
    if (power > 100) power = 100;
    if (power < -100) power = -100;
    
    chassis.setPower(power, power, power, power); 

    // debug to screen
    pros::lcd::print(0, "AVG: %.1f TGT: %.1f PWR: %.1f", avg, target, power);

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
  
  // FIX: Using the dot operator (.) instead of the arrow operator (->)
  chassis.resetEncoders();
  PID pid(kP, kI, kD, "TurnPID");
  double target = degrees * 1.5; // Turn factor may need tuning
  pid.setTarget(target);

  while (true) {
    double avg = chassis.averagePositionDeg();
    double power = pid.update(avg);
    if (power > 80) power = 80;
    if (power < -80) power = -80;
    
    chassis.setPower(-power, -power, power, power); // Left backward, Right forward
    pros::lcd::print(0, "TURN AVG: %.1f PWR: %.1f", avg, power);
    if (std::fabs(pid.error) < 10.0) break;
    pros::delay(20);
  }
  chassis.stop();
}

void turnRight(double degrees, double kP, double kI, double kD) {
  // Call turnLeft with negative degrees to turn right
  turnLeft(-degrees, kP, kI, kD);
}

void myAuton() {
  // Example usage (assuming this is your current auton)
  driveForward(24.0);
  turnRight(90.0);
  driveForward(12.0);
}

} // namespace Auton