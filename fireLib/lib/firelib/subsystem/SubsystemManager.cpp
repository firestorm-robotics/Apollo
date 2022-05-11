#include "lib/firelib/subsystem/SubsystemManager.hpp"

SubsystemManager::SubsystemManager(SubsystemList list) {
    _allSubsystems = list; 
}

/**
 * @brief updates the smartdashboard with telemetry from the subsystems
 * 
 */
void SubsystemManager::outputToSmartDashoard() {
    for (auto s : _allSubsystems) {
        s -> updateSmartDashboard();
    }
}

/**
 * @brief adds a looper that runs when the robot is enabled 
 * 
 * @param enabledLooper the looper to run the subsystems
 */
void SubsystemManager::registerEnabledLoops(std::shared_ptr<Looper> enabledLooper) {
    auto enabledLoop = std::make_shared<Loop>();


    enabledLoop -> setStart([&](units::second_t timestamp) {
        for (auto l : _loops) {
            l -> onStart(timestamp);
        }
    });

    enabledLoop -> setLoop([&](units::second_t timestamp) {
        for (auto subsystem : _allSubsystems) {
            subsystem -> pollTelemetry();
            subsystem -> updateSmartDashboard();
        }

        for (auto l : _loops) {
            l -> onLoop(timestamp);
        }
    });

    enabledLoop -> setStop([&](units::second_t timestamp) {
        for (auto l : _loops) {
            l -> onStop(timestamp);
        }

    });

    for (auto subsystem : _allSubsystems) {
        subsystem -> registerEnabledLoops(*this);
    }

    enabledLooper -> registerLoop(enabledLoop);
}

/**
 * @brief adds a looper that runs when the robot is disabled 
 * 
 * @param disabledLooper the looper that runs the robot
 */
void SubsystemManager::registerDisabledLoops(std::shared_ptr<Looper> disabledLooper) {
    auto disabledLoop = std::make_shared<Loop>();

    disabledLoop -> setStart([&](units::second_t timestamp) {/*disabled looper doesn't init anything*/});
    disabledLoop -> setLoop([&](units::second_t timestamp) {
        for (auto subsystem : _allSubsystems) {
            subsystem -> pollTelemetry(); 
            subsystem -> updateSmartDashboard(); 
        }
    });
    disabledLoop -> setStop([&](units::second_t timestamp) {});
    
    disabledLooper -> registerLoop(disabledLoop);
}

/**
 * @brief adds a loop, subsystem in this case, to be ran
 * 
 * @param loop the subsystem to run 
 */
void SubsystemManager::registerLoop(std::shared_ptr<Loop> loop) {
    _loops.push_back(loop);
}