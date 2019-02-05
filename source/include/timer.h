#ifndef __TIMER__DASHER
#define __TIMER__DASHER

/*
    Timestep is represented in milliseconds
    1000ms = 1s

*/

namespace T_FPSTimer
{
    uint64_t start_counter   = 0;
    uint64_t end_counter     = 0;

    double delta_time        = 0.0f;

    double target_time       = (1.0f/60.0f)*1000;

    double time_counter = 0;
    uint64_t frame_counter = 0;


    void GetTimeStep();
    void ChangeTargetSeconds();

}

#endif