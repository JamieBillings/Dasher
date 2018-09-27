#include "headers\\entity.h"

Texture BaseEntity::sprite;

namespace Entity
{
	BaseEntity player;
	BaseEntity enemy1;

	namespace Private
	{
		
	}

	void Init()
	{
		BaseEntity::sprite.Load("Dev\\Images\\SimonSpriteSheet.png");
	}

	void Deinit()
	{
		BaseEntity::sprite.Unload();
	}

	void Create(BaseEntity* _self, SDL_Rect _base_pos)
	{
		float temp_still_animation_frame_durations[5] 		= {1.00, 1.00, 1.00, 1.00};
		float temp_running_animation_frame_durations[5] 	= {1.00, 1.00, 1.00, 1.00};
		float temp_jumping_animation_frame_durations[4] 	= {1.00, 1.00, 1.00};
		//float temp_attacking_animation_frame_durations[5] 	= {1.00, 1.00, 1.00, 1.00};

		_self->base_animation.set(_base_pos, 5, temp_still_animation_frame_durations);
		_base_pos.y += _base_pos.h; 
		_self->walking_animation.set(_base_pos, 5, temp_running_animation_frame_durations);
		_base_pos.y += _base_pos.h;
		_self->jumping_animation.set(_base_pos, 4, temp_jumping_animation_frame_durations);

		if(_self->identifer && EntityIdentifer::is_player == EntityIdentifer::is_player){
			
		}
	}


}

void BaseEntity::Create(SDL_Rect _src_pos)
{
	float temp[5] = {1.00,1.00,1.00,1.00};
	base_animation.Set(_src_pos,5,temp);

	pos_x = 320;
	pos_y = 240;
	width = _src_pos.w;
	height = _src_pos.h;
	
}

void BaseEntity::Update()
{
	//printf("delta_time: %f\n", Timer::delta_time);
	//if(!grounded){pos_y = pos_y + (10 * Timer::delta_time);}
}

void BaseEntity::Render()
{
	
}

void BaseEntity::Destroy()
{

}

void BaseEntity::Jump()
{
	
}

void Player::Create(SDL_Rect _src_pos)
{
	//Setting Up Animations for Player
	float temp_walking[5]{0.08,0.08,0.08,0.08};
	SDL_Rect walking_pos = {0,47,32,47};
	walking_animation.Set(walking_pos,4,temp_walking);
	SDL_Rect base_pos = {0,0,32,47};
	float temp_base[11]{2.0,0.08,0.08,0.08,0.08,1.00,0.08,0.08,0.08,0.08};
	base_animation.Set(base_pos,10,temp_base);

	pos_x = 320;
	pos_y = 322 - 64;
	width = _src_pos.w;
	height = _src_pos.h;

	max_velocity.Create(3.4,5);
}

void Player::Render()
{
	int temp_x = static_cast<int>(pos_x);
	int temp_y = static_cast<int>(pos_y);
	sprite.dst_pos = {temp_x, temp_y, width, height};

	Animation* current_animation = &base_animation;; 
	if(is_base){current_animation = &base_animation;}
	else if(is_walking){current_animation = &walking_animation;}
	else if(is_jumping){current_animation = &jumping_animation;}

	if(flipped){sprite.Render(current_animation, SDL_FLIP_HORIZONTAL);}
	else{sprite.Render(current_animation);}
}

void Player::HandleEvents(SDL_Event* _event)
{
	if(_event->type == SDL_KEYDOWN){
		switch(_event->key.keysym.sym){
			case SDLK_UP:
				walk_up = true;
				break;
			case SDLK_RIGHT:
				walk_right = true;
				break;
			case SDLK_DOWN:
				walk_down = true;
				break;
			case SDLK_LEFT:
				walk_left = true;
				break;
			default:
				break;
		}
	}
	if(_event->type == SDL_KEYUP){
		switch(_event->key.keysym.sym){
			case SDLK_UP:
				walk_up = false;
				break;
			case SDLK_RIGHT:
				walk_right = false;
				break;
			case SDLK_DOWN:
				walk_down = false;
				break;
			case SDLK_LEFT:
				walk_left = false;
				break;
			default:
				break;
		}
	}
}

void Player::Update()
{
	//
	if(walk_left){
		flipped = true;
		velocity.x -= 0.08;
		if(velocity.x < -(max_velocity.x)){velocity.x = -(max_velocity.x);}
	}
	else{
		if(velocity.x < 0){
			(velocity.x > -1 && velocity.x < 0) ? velocity.x = 0 : velocity.x += 0.72;
		}
	}
	//
	if(walk_right){
		flipped = false;
		velocity.x += 0.08;
		if(velocity.x > max_velocity.x){velocity.x = max_velocity.x;}
	}
	else{
		if(velocity.x > 0){
			if(velocity.x < 1 && velocity.x > 0){velocity.x = 0;}
			else{velocity.x -= 0.72;}
		}
	}
	//
	if(walk_up){
		if(grounded){
			grounded = false;
			velocity.y = -5;
		}
	}
	//
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

void Player::Destroy()
{

}