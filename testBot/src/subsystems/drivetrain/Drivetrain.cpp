#include "src/subsystems/drivetrain/Drivetrain.hpp"


Drivetrain::Drivetrain() {
    _backLeft.Follow(_frontLeft,false);
    _frontRight.SetInverted(true);
    _backRight.Follow(_frontRight, true);
}


void Drivetrain::setMotorPower(double left, double right) {
    std::lock_guard<std::mutex> lg(lock);
    _frontLeft.Set(left);
    _frontRight.Set(right);
}

void Drivetrain::setIO(double throttle, double rotationVel) {
    std::lock_guard<std::mutex> lg(lock);
    PeriodicIO.throttle = throttle;
    PeriodicIO.rotationalVel = rotationVel;
}

void Drivetrain::pollTelemetry() {
    std::lock_guard<std::mutex> lg(lock);
    PeriodicIO.leftVel  = _frontLeft.GetEncoder().GetVelocity(); 
    PeriodicIO.rightVel = _frontRight.GetEncoder().GetVelocity(); 
}

void Drivetrain::updateSmartDashboard() {
    std::lock_guard<std::mutex> lg(lock);
    frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Drivetrain");

    tab.AddNumber("Left Velocity", [&](){return PeriodicIO.leftVel;});
    tab.AddNumber("Right Velocity", [&](){return PeriodicIO.rightVel;});
}

void Drivetrain::registerEnabledLoops(ILooper& looper) {
    auto loop = std::make_shared<Loop>();

    loop -> setStart([&](units::second_t) {_currentState = IDLE;});
    
    
    loop -> setLoop([&](units::second_t) {
        std::lock_guard<std::mutex> lg(lock);
        switch (_currentState) {
            case IDLE: {
                setMotorPower(0,0);
                break; 
            }
            case OPEN_LOOP: {
                auto [left, right] = _drive.toMotorPower(PeriodicIO.rotationalVel, PeriodicIO.throttle);
                setMotorPower(left, right);
                break; 
            }
        }
    });

    loop -> setStop([&](units::second_t){
        setMotorPower(0,0);
        _currentState = IDLE; 
    });

    looper.registerLoop(loop);
}