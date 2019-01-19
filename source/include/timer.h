#ifndef __TIMER__DASHER
#define __TIMER__DASHER

namespace T_Timer
{
    uint64_t start_time;
    uint64_t current_time;

    float frame_rate;


    void Start();

    void Destroy();
}