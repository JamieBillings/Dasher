namespace T_FPSTimer
{

void ChangeTargetSeconds(double _fps)
{
    if(_fps == -1){
        target_time = -1;
        return;
    }

    target_time = (1.0f/_fps)*1000;
}

//Almost gets the target fps constantly (sometimes on or two frames too fast)
//@remove print statements
void GetTimeStep()
{
    end_counter = SDL_GetPerformanceCounter();
    delta_time = static_cast<double>((end_counter - start_counter)*1000)/SDL_GetPerformanceFrequency();
    //printf("SLEEP: %f\n", target_time - delta_time);
    if(delta_time < target_time){
        uint32_t sleep_time = static_cast<uint32_t>(target_time - delta_time);
        SDL_Delay(sleep_time);
        delta_time = static_cast<double>((SDL_GetPerformanceCounter() - start_counter)*1000)/SDL_GetPerformanceFrequency();
    }

    time_counter += delta_time;
    //printf("TIME BASE: %f\n", time_counter);
    frame_counter++;

    if(time_counter >= 1000.0f){
        //printf("TIME: %f\n", time_counter);
        //printf("FPS: %lli\n", frame_counter);
        time_counter = 0;
        frame_counter = 0;
    } 

    start_counter = SDL_GetPerformanceCounter();
}



}