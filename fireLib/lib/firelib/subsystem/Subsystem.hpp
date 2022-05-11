#pragma once

#include <memory>
#include <mutex>
#include "lib/firelib/looper/Looper.hpp"

class ISubsystem {
protected: 
    std::mutex lock; 

public: 
    virtual void updateSmartDashboard() = 0;
    virtual void pollTelemetry() = 0;
    virtual void registerEnabledLoops(ILooper& enabledLooper) = 0;
    virtual ~ISubsystem() {}

};