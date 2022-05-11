#include "src/subsystems/drivetrain/DriveKinematics.hpp"

void DriveKinematics::updateWheelVelcity(double left, double right) {
    _leftVel  = left;
    _rightVel = right;
}


DriveSignal ArcadeKinematics::toMotorPower(double x, double y) {
    double max   = std::fmax(x, y);
    double total = y + x; 
    double diff  = y - x;

    double left  = 0;
    double right = 0;

    if (y >= 0) {
        if (x >= 0) {
            left  = max; 
            right = diff;
        } else {
            left  = total; 
            right = max; 
        }
    } else {
        if (x >= 0) {
            left  = total; 
            right = -max;  
        } else { 
            left  = -max; 
            right = total; 
        }
    }

    return std::make_tuple(left,right);
}

DriveSignal ArcadeKinematics::toWheelSpeeds(double x, double y) {
    auto [left, right] = toMotorPower(x ,y);

    double leftWheelVel  = (left * _motorRPM * _gearRatio) * (_wheelDiameter * M_PI);
    double rightWheelVel = (right * _motorRPM * _gearRatio) * (_wheelDiameter * M_PI); 

    if (std::abs(leftWheelVel - _leftVel) > _maxAccel) {
        if (leftWheelVel < 0) {
            leftWheelVel = _leftVel - (_maxAccel * 0.005);
        } else {
            leftWheelVel = _leftVel + (_maxAccel * 0.005);
        }
    } 

    if (std::abs(rightWheelVel - _rightVel) > _maxAccel) {
        if (rightWheelVel < 0) {
            rightWheelVel = _rightVel - (_maxAccel * 0.005);
        } else {
            rightWheelVel = _rightVel + (_maxAccel * 0.005);
        }
    }

    return std::make_tuple(leftWheelVel, rightWheelVel);
}


DriveSignal CurvatureKinematics::toWheelSpeeds(double x, double y) {
    return std::make_tuple(0,0);
}

DriveSignal CurvatureKinematics::toMotorPower(double x, double y) {
    return std::make_tuple(0,0);
}