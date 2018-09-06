namespace Events
{

bool GetEvents()
{
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){return false;}

		if(event.type == SDL_MOUSEMOTION){
			SDL_GetMouseState(&mouse_x,&mouse_y);
			Mouse::scaled_global_mouse_x = ((Events::mouse_x - Camrea::offset_x) / Renderer::render_scale) / 32;
			Mouse::scaled_global_mouse_y = ((Events::mouse_y - Camrea::offset_y) / Renderer::render_scale) / 32;
		}

		if(game_state == Game){
			GameEvents(&event);
		}

		if(game_state == Level_Select){
			int pos_x = Mouse::scaled_global_mouse_x * 32;
			int pos_y = Mouse::scaled_global_mouse_x * 32;
			Menu::Event();

			if(event.type == SDL_MOUSEBUTTONDOWN){
				for(int i = 0; i < 7; i++){
					if((pos_x > Menu::buttons[i].x) && (pos_x < Menu::buttons[i].x + Menu::buttons[i].w)){
						if((pos_y > Menu::buttons[i].y) && (pos_y < Menu::buttons[i].y + Menu::buttons[i].h)){
							Menu::btn_list[i].state = MBtn_State::Press;
						}
					}
				}

				if((pos_x > 9) && (pos_x < (9 + 68))){
					if((pos_y > 331) && (pos_y < 331 + 68)){
						Menu::settings_btn_state = MBtn_State::Press;
					}
				}

				if((pos_x > 494) && (pos_x < (494 + 68))){
					if((pos_y > 331) && (pos_y < 331 + 68)){
						Menu::lvl_editor_btn_state = MBtn_State::Press;
					}
				}
			}

			if(event.type == SDL_MOUSEBUTTONUP){
				for(int i = 0; i < 7; i++){
					if((pos_x > Menu::buttons[i].x) && (pos_x < Menu::buttons[i].x + Menu::buttons[i].w)){
						if((pos_y > Menu::buttons[i].y) && (pos_y < Menu::buttons[i].y + Menu::buttons[i].h)){
							Menu::selected_level = i;
							Menu::btn_list[i].Action();
						}
					}
				}

				if((pos_x > 9) && (pos_x < (9 + 68))){
					if((pos_y > 331) && (pos_y < 331 + 68)){
						//Settings Button Action Goes here!
					}
				}

				if((pos_x > 494) && (pos_x < (494 + 68))){
					if((pos_y > 331) && (pos_y < 331 + 68)){
						//Level Editor Button Action Goes here!
					}
				}
			}
		}

	}

	return true;
}


void GameEvents(SDL_Event* _event)
{
	if(_event.type == SDL_KEYUP){
		switch(event.key.keysym.sym){
			case SDLK_1:
				if(Mouse::selected_object->id == OBJ_TELE){
					delete Mouse::selected_object;
					Mouse::selected_object = new Empty;
				}
				else{
					delete Mouse::selected_object;
					Mouse::selected_object = new Teleporter;
				}
			break;

			case SDLK_2:
				if(Mouse::selected_object->id == OBJ_BOUNCE){
					delete Mouse::selected_object;
					Mouse::selected_object = new Empty;
				}
				else{
					delete Mouse::selected_object;
					Mouse::selected_object = new Bounce;
				}
			break;

			case SDLK_3:
				if(Mouse::selected_object->id == OBJ_FAN){
					delete Mouse::selected_object;
					Mouse::selected_object = new Empty;
				}
				else{
					delete Mouse::selected_object;
					Mouse::selected_object = new Fan;
				}
			break;

			case SDLK_r:
					Ball::Start(Ball::start_pos_x,Ball::start_pos_y);
					Map::Load(Menu::btn_list[Menu::selected_level].level);
			break;
			/*
			case SDLK_w:
				if(Mouse::selected_object->id == OBJ_WALL){
					delete Mouse::selected_object;
					Mouse::selected_object = new Empty;
				}
				else{
					delete Mouse::selected_object;
					Mouse::selected_object = new Wall;
				}
			break;

			case SDLK_e:
				if(Mouse::selected_object->id == OBJ_END){
					delete Mouse::selected_object;
					Mouse::selected_object = new Empty;
				}
				else{
					delete Mouse::selected_object;
					Mouse::selected_object = new Objective;
				}
			break;
			*/

			case SDLK_SPACE:
				if(Ball::frozen){Ball::frozen = false;}
				else if(!Ball::frozen){
					Ball::Start(Ball::start_pos_x, Ball::start_pos_y);
				}
			break;

			case SDLK_f:
				if(Mouse::selected_object->id != OBJ_NONE){
					Mouse::selected_object->flipped = !Mouse::selected_object->flipped;
				}
			break;

			case SDLK_ESCAPE:
				game_state = Level_Select;
			break;
		}
	}

	if(event.type == SDL_MOUSEBUTTONUP){
		int pos_x = Mouse::scaled_global_mouse_x;
		if(pos_x < 0 || pos_x > 20){break;}
		int pos_y = Mouse::scaled_global_mouse_y;
		if(pos_y < 0 || pos_y > 15){break;}
		if(Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->id != OBJ_WALL && Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->id != OBJ_END && Ball::frozen){
			if(Mouse::selected_object->id == OBJ_NONE){
				delete Map::map_array[pos_y * Map::MAP_WIDTH + pos_x];
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x] = new Empty;
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->pos_x = Mouse::selected_object->pos_x;
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->pos_y = Mouse::selected_object->pos_y;
			}
			else if(Mouse::selected_object->id == OBJ_TELE && Map::tele_count < Map::tele_limit){
				delete Map::map_array[pos_y * Map::MAP_WIDTH + pos_x];
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x] = new Teleporter;
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->Move(Mouse::selected_object);
			}
			else if(Mouse::selected_object->id == OBJ_BOUNCE && Map::bounce_count < Map::bounce_limit){
				delete Map::map_array[pos_y * Map::MAP_WIDTH + pos_x];
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x] = new Bounce;
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->Move(Mouse::selected_object);
			}
			else if(Mouse::selected_object->id == OBJ_FAN && Map::fan_count < Map::fan_limit){
				delete Map::map_array[pos_y * Map::MAP_WIDTH + pos_x];
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x] = new Fan;
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->Move(Mouse::selected_object);
			}
			/*
			else if(Mouse::selected_object->id == OBJ_WALL){
				delete Map::map_array[pos_y * Map::MAP_WIDTH + pos_x];
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x] = new Wall;
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->Move(Mouse::selected_object);
			}
			else if(Mouse::selected_object->id == OBJ_END){
				delete Map::map_array[pos_y * Map::MAP_WIDTH + pos_x];
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x] = new Objective;
				Map::map_array[pos_y * Map::MAP_WIDTH + pos_x]->Move(Mouse::selected_object);
			}*/
		}
	}
}

void EditorEvents()
{

}

void MenuEvents()
{

}


}