#pragma once
#include "main.h"

class Treads {
public:
  Treads(pros::Motor& m);
  void spinForward(int pct = 30);
  void spinReverse(int pct = 30);
  void stop();
private:
  pros::Motor& motor_;
};
