#ifndef TIME_INCLUDED
#define TIME_INCLUDED

//stuff
namespace Timer
{
	float start_counter;
	float current_counter;
	float frequency;
	float delta_time = 0;

	float target_seconds = 1.0f / 60.0f;


	void CapFramerate(); 
}

#endif