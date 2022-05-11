#pragma once 

#include "lib/firelib/looper/Looper.hpp"
#include "lib/firelib/looper/Loop.hpp"
#include "lib/firelib/subsystem/Subsystem.hpp"


#include <memory>
#include <vector>

using SubsystemList = std::vector<std::shared_ptr<ISubsystem>>;

class SubsystemManager : public ILooper {
private: 
    SubsystemList _allSubsystems;
    std::vector<std::shared_ptr<Loop>> _loops; 


public: 
    SubsystemManager(SubsystemList list);
    ~SubsystemManager() {}
    void outputToSmartDashoard();
    void registerLoop(std::shared_ptr<Loop> loop) override;
    void registerEnabledLoops(std::shared_ptr<Looper> enabledLooper);
    void registerDisabledLoops(std::shared_ptr<Looper> disabledLooper);


};