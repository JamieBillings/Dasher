namespace Game
{
	EntityStruct player;
	Texture background;
	SDL_Point ground = {0, 322}; 

	float map_offset = 0;

	bool Event(SDL_Event* event)
	{
		const uint8_t* state = SDL_GetKeyboardState(NULL);

		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT){return false;}

			
			Entity::HandleEvents(event);

		}

		return true;
	}

	void Init()
	{
		Init::Init();
		Window::CreateWindow();
		Renderer::CreateRenderer();

		Entity::Init();
		background.Load("Dev\\Images\\ground--temp.png");

		SDL_Rect temp = {0,47,32,47};
		Enitiy::Create(player, temp);

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

		if(entity_render_queue[0]->velocity.x > 0 && entity_render_queue[0]->pos_x + entity_render_queue[0]->width == 380){
			map_offset += entity_render_queue[0]->velocity.x;
		}
		printf("Map Offset = %f\n", static_cast<float>(map_offset));
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