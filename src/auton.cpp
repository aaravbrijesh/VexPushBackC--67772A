#include "auton.hpp"
#include "pid.hpp"
#include <cmath>

namespace Auton {

static double inchesToDegrees(double inches, double wheel_diameter) {
  return (inches / (M_PI * wheel_diameter)) * 360.0;
}

void driveForward(double inches, double wheel_diameter, double kP, double kI, double kD) {
  
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
  
  chassis.resetEncoders();
  PID pid(kP, kI, kD, "StrafePID");
  double target = inchesToDegrees(inches, wheel_diameter);
  pid.setTarget(target);

  while (true) {
    double avg = chassis.averagePositionDeg();
    double power = pid.update(avg);
    if (power > 100) power = 100;
    if (power < -100) power = -100;

    double fl = -power;
    double bl = power;
    double fr = power;
    double br = -power;
    chassis.setPower(fl, bl, fr, br);

    pros::lcd::print(0, "STRAFE AVG: %.1f PWR: %.1f", avg, power);
    if (std::fabs(pid.error) < 10.0) break;
    pros::delay(20);
  }
  chassis.stop();
}

void strafeRight(double inches, double wheel_diameter, double kP, double kI, double kD) {
  
  chassis.resetEncoders();
  PID pid(kP, kI, kD, "StrafePID");
  double target = inchesToDegrees(inches, wheel_diameter);
  pid.setTarget(target);

  while (true) {
    double avg = chassis.averagePositionDeg();
    double power = pid.update(avg);
    if (power > 100) power = 100;
    if (power < -100) power = -100;

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

void turnLeft(double degrees, double kP, double kI, double kD) {
  
  chassis.resetEncoders();
  PID pid(kP, kI, kD, "TurnPID");
  double target = degrees * 1.5;
  pid.setTarget(target);

  while (true) {
    double avg = chassis.averagePositionDeg();
    double power = pid.update(avg);
    if (power > 80) power = 80;
    if (power < -80) power = -80;
    chassis.setPower(-power, -power, power, power);
    pros::lcd::print(0, "TURN AVG: %.1f PWR: %.1f", avg, power);
    if (std::fabs(pid.error) < 10.0) break;
    pros::delay(20);
  }
  chassis.stop();
}

void turnRight(double degrees, double kP, double kI, double kD) {
  
  chassis.resetEncoders();
  PID pid(kP, kI, kD, "TurnPID");
  double target = degrees * 1.5;
  pid.setTarget(target);

  while (true) {
    double avg = chassis.averagePositionDeg();
    double power = pid.update(avg);
    if (power > 80) power = 80;
    if (power < -80) power = -80;
    chassis.setPower(power, power, -power, -power);
    pros::lcd::print(0, "TURN AVG: %.1f PWR: %.1f", avg, power);
    if (std::fabs(pid.error) < 10.0) break;
    pros::delay(20);
  }
  chassis.stop();
}

void myAuton() {
  // a small example autonomous routine
  pros::lcd::clear();
  pros::lcd::print(0, "Running Auton");
  driveForward(24.0);
  pros::delay(200);
  turnRight(90.0);
  pros::delay(200);
  driveBackward(12.0);
}

} // namespace Auton
