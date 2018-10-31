namespace Game
{
	EntityStruct player;
	EntityStruct entity_render_queue[100];
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
		background.Load("bin\\images\\ground-temp.png");

		SDL_Rect temp = {0,0,64,64};
		player.identifier |= EntityIdentifier::is_player;
		Entity::Create(&player, temp);

		EntityStruct empty_entity;
		SDL_Rect empty_struct = {0,0,0,0};
		Entity::Create(&empty_entity, empty_struct);

		for(int i = 0; i < 100; i++){
			entity_render_queue[i] = empty_entity;
		}
		entity_render_queue[0] = player;
	}

	void GameLoop()
	{
		for(int i = 0; i < 100; i++){
			if((entity_render_queue[i].identifier & EntityIdentifier::is_unknown) == EntityIdentifier::is_unknown){
				Entity::Update(&entity_render_queue[i]);
				if((EntityState::is_grounded & entity_render_queue[i].state) == EntityState::is_grounded){
					if(entity_render_queue[i].pos_y + entity_render_queue[i].height > ground.y){
						entity_render_queue[i].pos_y = ground.y - entity_render_queue[i].height;
						entity_render_queue[i].state |= EntityState::is_grounded;
					}
				}
			}
		}

		if(entity_render_queue[0].velocity.x > 0 && entity_render_queue[0].pos_x + entity_render_queue[0].width == 380){
			map_offset += entity_render_queue[0].velocity.x;
		}
		//printf("Map Offset = %f\n", static_cast<float>(map_offset));
	}

	void Render()
	{
		//Render Code here	
		background.Render();

		for(int i = 0; i < 100; i++){
			if(entity_render_queue[i].identifier != EntityIdentifier::is_unknown){
				Entity::Render(&entity_render_queue[i]);
				printf("PLAYER POS X= %f Y= %f W=%d H=%d \n", entity_render_queue[i].pos_x,
					entity_render_queue[i].pos_y, entity_render_queue[i].width, entity_render_queue[i].height);
			}
		}
	}

	void Destroy()
	{
		//BaseEntity::Deinit();

		Renderer::DestroyRenderer();
		Window::DestroyWindow();
	}
}