namespace Game
{
	Player player;
	Texture background;
	SDL_Point ground = {0, 322}; 

	bool Event(SDL_Event* event)
	{
		const uint8_t* state = SDL_GetKeyboardState(NULL);

		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT){return false;}

			
			player.HandleEvents(event);

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
		for(int i = 0; i < 100; i++){
			if(entity_render_queue[i] != nullptr){
				entity_render_queue[i]->Update();
				if(!entity_render_queue[i]->grounded){
					if(entity_render_queue[i]->pos_y + entity_render_queue[i]->height > ground.y){
						entity_render_queue[i]->pos_y = ground.y - entity_render_queue[i]->height;
						entity_render_queue[i]->grounded = true;
					}
				}
			}
		}
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