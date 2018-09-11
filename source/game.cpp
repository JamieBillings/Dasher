namespace Game
{
	Player player;

	bool Event(SDL_Event* event)
	{
		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT){return false;}

			uint8_t* state = SDL_GetKeyboardState(NULL);
			if(state[SDL_SCANCODERIGHT]){}
		}

		return true;
	}

	void Init()
	{
		Init::Init();
		Window::CreateWindow();
		Renderer::CreateRenderer();

		SDL_Rect temp = {0,0,32,64};
		player.Create(temp);

		for(int i = 0; i < 100; i++){
			entity_render_queue[i] = nullptr;
		}
		entity_render_queue[0] = &player;
	}

	void GameLoop()
	{

	}

	void Render()
	{
		//Render Code here	

		for(int i = 0; i < 100; i++){
			if(entity_render_queue[i] != nullptr){entity_render_queue.Render();}
		}
	}

	void Destroy()
	{
		Renderer::DestroyRenderer();
		Window::DestroyWindow();
	}
}