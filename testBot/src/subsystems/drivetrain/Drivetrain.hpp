#pragma once

#include "lib/firelib/subsystem/Subsystem.hpp"
#include <rev/CANSparkMax.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include "src/subsystems/drivetrain/DriveKinematics.hpp"
#include <memory>


class Drivetrain : public ISubsystem, std::enable_shared_from_this<Drivetrain> {
    private: 
         rev::CANSparkMax _frontLeft{1, rev::CANSparkMax::MotorType::kBrushless};
         rev::CANSparkMax _backLeft{2, rev::CANSparkMax::MotorType::kBrushless};
         rev::CANSparkMax _frontRight{3, rev::CANSparkMax::MotorType::kBrushless};
         rev::CANSparkMax _backRight{4, rev::CANSparkMax::MotorType::kBrushless};

        
        ArcadeKinematics _drive{12, 6, 0, 6, 0.012, 5000}; 
         struct {
             double throttle = 0;
             double rotationalVel = 0;

             double leftVel = 0;
             double rightVel = 0;
         } PeriodicIO; 

         void setMotorPower(double left, double right);

    public: 
        Drivetrain(); 
        enum State {IDLE, OPEN_LOOP};
        State _currentState; 
        void updateSmartDashboard() override;
        void pollTelemetry() override;
        void registerEnabledLoops(ILooper& enabledLooper) override; 

        void setIO(double throttle, double rotationalVel); 
        
        std::shared_ptr<Drivetrain> getptr() {return shared_from_this();}
};