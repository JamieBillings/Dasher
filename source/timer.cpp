namespace T_FPSTimer
{

void ChangeTargetSeconds(double _fps)
{
    if(_fps == -1){
        target_time = -1;
        return;
    }

    target_time = 1.0f/_fps;
}

void GetTimeStep()
{
    end_counter = SDL_GetPerformanceCounter();

    double counter_diffrence = static_cast<double>((end_counter - start_counter))/SDL_GetPerformanceFrequency();
    counter_diffrence *= 1000;

    printf("counter time: %f \n", counter_diffrence);
    printf("target_time: %f \n", target_time);
    if(counter_diffrence < (target_time * 1000)){
        uint32_t sleep_time = static_cast<uint32_t>(counter_diffrence - target_time);
        printf("(SLEEP TIME) %d \n", sleep_time);
        SDL_Delay(sleep_time);
        counter_diffrence = static_cast<double>((SDL_GetPerformanceCounter() - start_counter)*1000)/SDL_GetPerformanceFrequency();
    }

    time_counter += counter_diffrence;
    frame_counter++;

    if(time_counter > 1000.0f){
        printf("frame_counter = %lld\n", frame_counter);
        time_counter = 0;
        frame_counter = 0;
    }

    start_counter = SDL_GetPerformanceCounter();
}


}