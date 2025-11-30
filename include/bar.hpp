#pragma once
#include "main.h"
#include "pid.hpp"

class Bar {
public:
  Bar(pros::Motor& m);
  void setTargetDeg(double deg);
  void updatePID();
  void holdPosition();
  void stop();
  double getPosition() const;   // ✅ ADD THIS
private:
  pros::Motor& motor_;
  PID pid_;
  double target_deg_;
  bool pid_active_;
};
