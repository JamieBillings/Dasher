namespace Game
{
	Player player;
	Texture background;

	bool Event(SDL_Event* event)
	{
		const uint8_t* state = SDL_GetKeyboardState(NULL);

		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT){return false;}

			
			if(state[SDL_SCANCODE_LEFT]){player.flipped = true;}
			if(state[SDL_SCANCODE_RIGHT]){player.flipped = false;}

		}

		return true;
	}

	void Init()
	{
		Init::Init();
		Window::CreateWindow();
		Renderer::CreateRenderer();

		BaseEntity::Init();
		background.Load("Dev\\Images\\ground--temp.png");

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
		background.Render();

		for(int i = 0; i < 100; i++){
			if(entity_render_queue[i] != nullptr){entity_render_queue[i]->Render();}
		}
	}

	void Destroy()
	{
		BaseEntity::Deinit();

		Renderer::DestroyRenderer();
		Window::DestroyWindow();
	}
}