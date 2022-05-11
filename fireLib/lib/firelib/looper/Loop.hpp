#pragma once

#include <units/time.h>
#include <functional>

using LoopCallback  = std::function<void(units::second_t)>;

class Loop {
    private: 
        LoopCallback startCallback;
        LoopCallback loopCallback;
        LoopCallback stopCallback; 

    public: 
        virtual ~Loop() {}
        void onStart(units::second_t timestamp) {startCallback(timestamp);}
        void onLoop(units::second_t timestamp)  {loopCallback(timestamp);}
        void onStop(units::second_t timestamp)  {stopCallback(timestamp);}

        void setStart(LoopCallback callback) {startCallback = callback;}
        void setLoop(LoopCallback callback)  {loopCallback  = callback;}
        void setStop(LoopCallback callback)  {stopCallback  = callback;}
        




};