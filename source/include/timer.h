#ifndef __TIMER__DASHER
#define __TIMER__DASHER

/*
    Timestep is represented in milliseconds
    1000ms = 1s

    Start() is just so the GetTimeStep() function can work on first loop.
*/

namespace T_FPSTimer
{
    uint64_t start_time;
    uint64_t current_time;

    float frame_rate;
    double time_step;

    enum ErrorID{
        zerodivision = 0
    };


    void Start();
    void GetTimeStep();

    void ErrorCatch(ErrorID _code);

    void Destroy();
}

#endif