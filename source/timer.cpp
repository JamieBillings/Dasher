namespace T_FPSTimer
{

void Start()
{
    start_time = SDL_GetPerformanceCounter();
}

void GetTimeStep()
{
    current_time = SDL_GetPerformanceCounter();
    double time_diffrence = static_cast<double>(current_time - start_time) * 1000;
    if(current_time == 0){
        ErrorCatch(ErrorID::zerodivision);
        return;
    }

    time_step = time_diffrence / SDL_GetPerformanceFrequency();
    start_time = SDL_GetPerformanceCounter();
}

void ErrorCatch(ErrorID _code)
{
    switch(_code){
        case ErrorID::zerodivision:
            std::string message1 = "Function GetTimeStep tried dividing by Zero \n";
            std::string message2 = "Please check T_FPSTimer::Start() function is called.";
            OS::CreateErrorWindow(message1 + message2, error_level::error);
            break;
    }
    
}

}