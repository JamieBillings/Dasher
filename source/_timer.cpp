namespace Timer
{

//@ This shit is a mess
void CapFramerate()
{
	float end_counter = static_cast<float>(SDL_GetPerformanceCounter());
	current_counter = end_counter - start_counter;
	current_counter /= frequency;

	if(current_counter < target_seconds){
		while(current_counter < target_seconds){
			uint32_t sleep_time = static_cast<uint32_t>(1000.0f * (target_seconds - current_counter));
			if(sleep_time > 0){SDL_Delay(sleep_time);}
			current_counter = static_cast<float>(SDL_GetPerformanceCounter()) - start_counter;
			current_counter = current_counter / frequency;
		}
	}
	else{
		printf("Target Framerate Missed 60! \n");
	}
	
	delta_time = (static_cast<float>(SDL_GetPerformanceCounter()) - start_counter) / frequency;
	//printf("Delta: %f\n",delta_time);
	Timer::start_counter = static_cast<float>(SDL_GetPerformanceCounter());
}

}