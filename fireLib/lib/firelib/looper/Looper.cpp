#include "lib/firelib/looper/Looper.hpp"


Looper::Looper() {

    _notifier = new frc::Notifier([&]{run();});
    _running = false; 

}

Looper::~Looper() {
    delete _notifier;
}

/**
 * @brief runs all the loops in _loops once
 * should be called @ 200hz
 */
void Looper::run() {
    units::second_t now = frc::Timer::GetFPGATimestamp();

    for (auto l : _loops) {
        l -> onLoop(now);
    }

    _dt = now - _timestamp;
    _timestamp = now; 

}

/**
 * @brief adds a loop to be ran 
 * 
 * @param loop the loop to be added
 */
void Looper::registerLoop(std::shared_ptr<Loop> loop) {
    _loops.push_back(loop);
}

/**
 * @brief called once, runs that start method of the loops
 * 
 */
void Looper::start() {
    if (!_running) {
        std::cout << "Starting loops" << std::endl; 
        _timestamp = frc::Timer::GetFPGATimestamp();
        for (auto l : _loops) {
            l -> onStart(_timestamp);
        }

        _running = true; 
    }

    _notifier -> StartPeriodic(K_DELTA_TIME);
}

/**
 * @brief called once, runs the stop method of the loops
 * 
 */
void Looper::stop() {
    if (_running) {
        std::cout << "stopping loops" << std::endl;
        _notifier -> Stop();
        _running = false; 
        _timestamp = frc::Timer::GetFPGATimestamp();

        for (auto l : _loops) {
            l -> onStop(_timestamp);
        }
    }
}
