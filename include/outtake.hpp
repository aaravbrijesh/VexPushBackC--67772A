#pragma once
#include "main.h"

class Outtake {
public:
  Outtake(pros::Motor& m);
  void spinIn(int pct = 100);
  void spinOut(int pct = 100);
  void moveTurns(double turns, int pct = 100);
  void stop();
private:
  pros::Motor& motor_;
};
