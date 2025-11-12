#include "vex.h"
#include "vex_competition.h"
#include "vex_drivetrain.h"
#include "vex_global.h"
#include "vex_motorgroup.h"
#include "vex_task.h"
#include "vex_units.h"
#include "vex_vision.h"
#include <iostream>

using namespace vex;
using namespace std;

// CONSTANT VARIABLES
brain       Brain;

vision::signature redSig = vision::signature(1, 14769, 15277, 15023, 697, 1137, 917, 11743288, 0);

// LEFT MOTORS
motor mt1 = motor(vex::PORT1);
motor mt2 = motor(vex::PORT11);
motor mt3 = motor(vex::PORT14);

// RIGHT MOTORS
motor mt4 = motor(vex::PORT2);
motor mt5 = motor(vex::PORT12);
motor mt6 = motor(vex::PORT13);

// Vision Sensor
vision vis1 = vision(vex::PORT19);

// Motor Groups
//motor_group mgL = motor_group(mt1, mt2, mt3);
//motor_group mgR = motor_group(mt4, mt5, mt6);

motor_group mgL = motor_group(mt1);
motor_group mgR = motor_group(mt4);


// Drivetrain
drivetrain dt = drivetrain(mgL, mgR);

// Controller
controller ct = controller();


// Declares that this program is used for competition use
competition Competition;

void colorCheck() {
    while(true) {
        vis1.takeSnapshot(redSig);
        if (vis1.objects[0].exists) {
            Brain.Screen.print("Red Object Found!");
        } else {
            Brain.Screen.print("Nothing found!");
        }
    }
}


void tempCheck() {
    Brain.Screen.print("Motor 1 Temperature is: %.2f%", mt1.temperature(celsius));
}

void axisChangedL() {
    // Axes of controller
    // LEFT JOYSTICK
    int ax3 = ct.Axis3.position(); // UD for LEFT JOYSTICK
    int ax4 = ct.Axis4.position(); // RL for LEFT JOYSTICK

    // RIGHT JOYSTICK
    int ax1 = ct.Axis1.position(); // RL for RIGHT JOYSTICK
    int ax2 = ct.Axis2.position(); // UD for RIGHT JOYSTICK

    mgL.convertVelocity(ax3, velocityUnits::pct);

    // Volt velocity
    //mgL.spin(fwd, 10, voltageUnits::volt)
    
}

void axisChangedR() {
    // Axes of controller

    // RIGHT JOYSTICK
    int ax1 = ct.Axis1.position(); // RL for RIGHT JOYSTICK
    int ax2 = ct.Axis2.position(); // UD for RIGHT JOYSTICK

    mgR.convertVelocity(ax2, velocityUnits::pct);

    // Volt velocity
    //mgL.spin(fwd, 10, voltageUnits::volt)
    
}

// Autonomous mode
void autonomous() {
    mt1.setVelocity(40, velocityUnits::pct);
    mt1.spin(vex::directionType::fwd);
}

// Teleoperated mode
void teleop() {
    
}

int main() {
    Brain.Screen.printAt( 10, 50, "this is the pushback" );

    ct.Axis2.changed(axisChangedR); // RIGHT JOYSTICK
    ct.Axis3.changed(axisChangedL); // LEFT JOYSTICK

    //colorCheck();
    
    // Initializes function for autonomous
    //Competition.autonomous(autonomous);
    //Competition.drivercontrol(teleop);

    // Start autonomous
    //autonomous();
}
