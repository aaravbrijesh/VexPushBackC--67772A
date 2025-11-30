#pragma once
#include "main.h"
#include <array>

class MecanumDrive {
public:
  MecanumDrive(pros::Motor& fl, pros::Motor& bl, pros::Motor& fr, pros::Motor& br);

  // fl, bl, fr, br are in percent (-100 .. 100)
  void setPower(double fl_pct, double bl_pct, double fr_pct, double br_pct);
  void stop();
  double averagePositionDeg();
  void resetEncoders();

private:
  pros::Motor& fl_;
  pros::Motor& bl_;
  pros::Motor& fr_;
  pros::Motor& br_;

  static int pctToVel(double pct); // converts -100..100 to -127..127
};
