#include "headers\\entity.h"



namespace Entity
{

	namespace Private
	{
		
	}

	void Init()
	{
		Private::sprite.Load("Dev\\Images\\SimonSpriteSheet.png");
	}

	void Deinit()
	{
		Private::sprite.Unload();
	}

	void Create(BaseEntity* _self, SDL_Rect _base_pos)
	{
		//Setting up player animation...
		float temp_still_animation_frame_durations[5] 		= {1.00, 1.00, 1.00, 1.00};
		float temp_running_animation_frame_durations[5] 	= {1.00, 1.00, 1.00, 1.00};
		float temp_jumping_animation_frame_durations[4] 	= {1.00, 1.00, 1.00};
		//float temp_attacking_animation_frame_durations[5] 	= {1.00, 1.00, 1.00, 1.00}; - not useable yet

		_self->base_animation.set(_base_pos, 5, temp_still_animation_frame_durations);
		_base_pos.y += _base_pos.h; 
		_self->walking_animation.set(_base_pos, 5, temp_running_animation_frame_durations);
		_base_pos.y += _base_pos.h;
		_self->jumping_animation.set(_base_pos, 4, temp_jumping_animation_frame_durations);

		if(EntityIdentifer::is_player && _self->identifer == EntityIdentifer::is_player){
			_self->pos_x = 320;
			_self->pos_y = 322 - 64;
			_self->max_velocity.Create(3.4,5);
		}
		else{
			_self->identifer = EntityIdentifer::is_unknown;
		}
	}

	void Update(BaseEntity* _self)
	{
		if(EntityState::is_grounded && _self->grounded != _self->grounded){pos_y = pos_y + (10 * Timer::delta_time)}


	}

	void Render(BaseEntity* _self)
	{
		int temp_x = static_cast<int>(_self->pos_x);
		int temp_y = static_cast<int>(_self->pos_y);
		sprite.dst_pos = {temp_x, temp_y, _self->width, _self->height};

		if(EntityState::is_still && _self->state == EntityState::is_still)			{current_animation = &_self->base_animation;}
		else if(EntityState::is_walking && _self->state == EntityState::is_walking)	{current_animation = &_self->walking_animation;}
		else if(EntityState::is_jumping && _self->state == EntityState::is_jumping)	{current_animation = &_self->jumping_animation;}
		else{
			current_animation = nullptr;
			printf("No Entity State Specified\n");
		}

		if(EntityState::is_flipped && ){sprite.Render(current_animation, SDL_FLIP_HORIZONTAL);}
		else{sprite.Render(current_animation);}
	}

	void Destroy(BaseEntity _self)
	{
		
	}


	void HandleEvents(SDL_Event* _event)
	{
		if(_event->type == SDL_KEYDOWN){
			switch(_event->key.keysym.sym){
				case SDLK_UP:
				key_held |= KeyHeld::jump_up;
				break;
			case SDLK_RIGHT:
				key_held |= KeyHeld::walk_right;
				break;
			case SDLK_DOWN:
				key_held |= KeyHeld::dive_down;
				break;
			case SDLK_LEFT:
				key_held |= KeyHeld::walk_left;
				break;
			default:
				break;
			}
		}

		if(_event-> type == SDL_KEYUP){
			switch(_event->key.keysym.sym){
			case SDLK_UP:
				key_held ^= KeyHeld::jump_up;
				break;
			case SDLK_RIGHT:
				key_held ^= KeyHeld::walk_right;
				break;
			case SDLK_DOWN:
				key_held ^= KeyHeld::dive_down;
				break;
			case SDLK_LEFT:
				key_held ^= KeyHeld::walk_left;
				break;
			default:
				break;
			}
		}
	}

	void MovePlayer(EntityStruct* _player)
	{
		if(KeyHeld::walk_left && key_held == KeyHeld::walk_left){
			_player->state |= EntityState::is_flipped;
			_player->velocity.x -= 0.08;
			if(_player->velocity.x < -(_player->max_velocity.x)){_player->velocity.x = -(_player->max_velocity.x);}
		}
		else{
			if(_player->velocity.x < 0){
				(_player->velocity.x > -1 && _player->velocity.x < 0) ? _player->velocity.x = 0 : _player->velocity.x += 0.72;
			}
		}
		
		if(KeyHeld::walk_right && key_held == KeyHeld::walk_right){
			_player->state ^= EntityState::is_flipped;
			_player->velocity.x += 0.08;
			if(_player->velocity.x > _player->max_velocity.x){_player->velocity.x = _player->max_velocity.x;}
		}
		else{
			if(_player->velocity.x > 0){
				(_player->velocity.x < 1 && _player->velocity.x > 0) ? _player->velocity.x = 0 : _player->velocity.x -= 0.72;
			}
		}


		if(KeyHeld::jump_up && key_held == KeyHeld::jump_up){
			if(KeyState::is_grounded && _player->state == KeyState::is_grounded){
				_player->state ^= EntityState::is_grounded;
				_player->velocity.y = -5;
			}
		}
		

		if(walk_down){
			if(!grounded){
				velocity.y += 0.8;
			}
		}

		if(!grounded){
			pos_y += (velocity.y * (100 * Timer::delta_time));
			velocity.y += GRAVITY;
			if(pos_y > 340){
				pos_y = 340;
				velocity.y = 0;
				grounded = true;
			}
		}

		pos_x += velocity.x * (100 * Timer::delta_time);

		if(pos_x < 0){
			pos_x = 0;
			velocity.x = 0;
		}

		if(pos_x + width > 380){pos_x = 380 - width;}

		if((walk_left || walk_right) && grounded){
			walking_animation.Progress();
			is_walking = true;
		}
		else{
			walking_animation.Stop();
			is_walking = false;
		}
			
		if(!is_walking && !is_jumping){
			base_animation.Progress();
			is_base = true;
		}
		else{
			base_animation.Stop();
			is_base = false;
		}

		printf("vel: %f \n", static_cast<float>(velocity.x));
	}
}