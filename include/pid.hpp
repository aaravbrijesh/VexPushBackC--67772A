#pragma once
#include <cmath>

class PID {
public:
  PID(double p = 0.0, double i = 0.0, double d = 0.0, const char* name = "PID")
    : kP(p), kI(i), kD(d), name(name), setpoint(0.0), error(0.0),
      prev_error(0.0), integral(0.0), derivative(0.0), output(0.0),
      integral_limit(200.0) {}

  void setTarget(double t) {
    setpoint = t;
    integral = 0.0;
    prev_error = 0.0;
  }

  double update(double current) {
    error = setpoint - current;
    integral += error;
    if (std::fabs(integral) > integral_limit) {
      integral = integral > 0 ? integral_limit : -integral_limit;
    }
    derivative = error - prev_error;
    prev_error = error;
    output = (kP * error) + (kI * integral) + (kD * derivative);
    return output;
  }

  double kP, kI, kD;
  const char* name;
  double setpoint;
  double error;
  double prev_error;
  double integral;
  double derivative;
  double output;
  double integral_limit;
};
