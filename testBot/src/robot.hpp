#pragma once

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/Notifier.h>
#include <units/time.h>
#include <memory>
#include "lib/firelib/looper/Looper.hpp"
#include "lib/firelib/subsystem/SubsystemManager.hpp"
#include "src/subsystems/drivetrain/Drivetrain.hpp"

class Robot : public frc::TimedRobot {
public:

    void RobotInit() override;
    void RobotPeriodic() override;

    void DisabledPeriodic() override; 

    void AutonomousInit() override; 
    void AutonomousPeriodic() override; 

    void TeleopInit() override;
    void TeleopPeriodic() override; 

private: 
    std::shared_ptr<Looper> _enabledLooper; 
    std::shared_ptr<Looper> _disabledLooper; 
    

    SubsystemList _subsystemList; 

    Drivetrain drivetrain;
    std::unique_ptr<SubsystemManager> _subsystemManager;
    
    bool _looperEnabled = false; 

    frc::Joystick _joystick{0};

};
