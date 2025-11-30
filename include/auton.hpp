#pragma once
#include "main.h"
#include "robot.hpp"

// High-level auton functions (you can add routines here)
namespace Auton {
  void driveForward(double inches, double wheel_diameter = 4.125, double kP = 0.35, double kI = 0.0, double kD = 0.25);
  void driveBackward(double inches, double wheel_diameter = 4.125, double kP = 0.35, double kI = 0.0, double kD = 0.25);
  void strafeLeft(double inches, double wheel_diameter = 4.125, double kP = 0.35, double kI = 0.0, double kD = 0.25);
  void strafeRight(double inches, double wheel_diameter = 4.125, double kP = 0.35, double kI = 0.0, double kD = 0.25);
  void turnLeft(double degrees, double kP = 0.35, double kI = 0.0, double kD = 0.25);
  void turnRight(double degrees, double kP = 0.35, double kI = 0.0, double kD = 0.25);

  // a simple example autonomous routine that calls helpers
  void simpleAuton();
}
