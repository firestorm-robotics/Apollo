#pragma once 

#include <tuple> 
#include <cmath>

using DriveSignal = std::tuple<double, double>;

class DriveKinematics {
    protected: 
        double _maxVel = 0;
        double _maxAccel = 0;
        double _trackWidth = 0; 
        double _wheelDiameter = 0;
        double _gearRatio = 0; 
        double _motorRPM = 0; 

        double _leftVel = 0;
        double _rightVel = 0; 

        DriveKinematics(double vel, double accel, double width, double diam, double gear, double rpm) : 
                        _maxVel(vel), _maxAccel(accel), _trackWidth(width), _wheelDiameter(diam),
                        _gearRatio(gear), _motorRPM(rpm) {

        } 

    public:  
        virtual ~DriveKinematics() {} 
        virtual DriveSignal toWheelSpeeds(double x, double y) = 0;
        virtual DriveSignal toMotorPower(double x, double y) = 0; 

        void updateWheelVelcity(double left, double right); 
        
};


class ArcadeKinematics : public DriveKinematics {
    public: 
        ArcadeKinematics(double vel, double accel, double width, double diam, double gear, double rpm) : 
                        DriveKinematics(vel, accel, width, diam, gear, rpm) {}

        ~ArcadeKinematics() {}
        DriveSignal toWheelSpeeds(double x, double y) override;
        DriveSignal toMotorPower(double x, double y) override; 

};

class CurvatureKinematics : public DriveKinematics {
    public: 
        CurvatureKinematics(double vel, double accel, double width, double diam, double gear, double rpm) : 
                        DriveKinematics(vel, accel, width, diam, gear, rpm) {}

        ~CurvatureKinematics() {}
        DriveSignal toWheelSpeeds(double x, double y) override;
        DriveSignal toMotorPower(double x, double y) override; 

};