#include "src/robot.hpp"




void Robot::RobotInit() {
    _enabledLooper  = std::make_shared<Looper>(); 
    _disabledLooper = std::make_shared<Looper>();

    _subsystemList.push_back(drivetrain.getptr());

    _subsystemManager = std::make_unique<SubsystemManager>(_subsystemList); 

    _subsystemManager -> registerEnabledLoops(_enabledLooper);
    _subsystemManager -> registerDisabledLoops(_disabledLooper); 

}


void Robot::RobotPeriodic() {


}

void Robot::DisabledPeriodic() {
    _enabledLooper -> stop();
    _disabledLooper -> start(); 
}

void Robot::AutonomousInit() {

}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
    if (!_looperEnabled) {
        _disabledLooper -> stop(); 
        _enabledLooper -> start(); 
        _looperEnabled = true; 
    }

}

void Robot::TeleopPeriodic() {

    double throttle = _joystick.GetY(); 
    double rot      = _joystick.GetX();

    drivetrain.setIO(throttle,rot);

}


#ifndef RUNNING_FRC_TESTS
int main() {return frc::StartRobot<Robot>();}
#endif
