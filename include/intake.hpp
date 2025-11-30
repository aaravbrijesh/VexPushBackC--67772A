#pragma once
#include "main.h"

class Intake {
public:
  Intake(pros::Motor& m);
  void spinOut(int pct = 100);
  void spinIn(int pct = 100);
  void moveTurns(double turns, int pct = 100);
  void stop();
private:
  pros::Motor& motor_;
};
