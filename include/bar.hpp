#ifndef BAR_HPP
#define BAR_HPP

#include "main.h"

class Bar {
public:
    Bar(pros::Motor& m);
    void setTargetDeg(double deg);
    void moveManual(int voltage);
    void stop();
    double getPosition() const;

private:
    pros::Motor& motor_;
};

// Align these names with robot.cpp
extern pros::Motor bar_motor;
extern Bar my_bar;
extern pros::Controller controller; // Changed from master to controller

void bar_control();

#endif