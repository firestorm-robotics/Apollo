#pragma once

#include <vector>
#include <memory>
#include <frc/Notifier.h>
#include <units/time.h>
#include <frc/Timer.h>
#include "lib/firelib/looper/Loop.hpp"
#include <iostream>



class ILooper {
public: 
    virtual void registerLoop(std::shared_ptr<Loop> loop) = 0;
    virtual ~ILooper() {}
};

class Looper : public ILooper {
private:
    std::vector<std::shared_ptr<Loop>> _loops;
    frc::Notifier* _notifier;
    static constexpr units::second_t K_DELTA_TIME = units::make_unit<units::second_t>(0.005);
    units::second_t _dt;
    units::second_t _timestamp;
    bool _running; 


public:
    Looper();
    ~Looper();
    void run();
    void registerLoop(std::shared_ptr<Loop> loop) override;
    void start(); 
    void stop(); 

};
