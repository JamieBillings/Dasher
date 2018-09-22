#include "headers\\entity.h"

Texture BaseEntity::sprite;

void BaseEntity::Init()
{
	sprite.Load("Dev\\Images\\SimonSpriteSheet.png");
	//32x47
}

void BaseEntity::Deinit()
{
	sprite.Unload();
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
	printf("delta_time: %f\n", Timer::delta_time);
	if(!grounded){pos_y = pos_y + (10 * Timer::delta_time);}
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
	float temp[5] = {0.08,0.08,0.08,0.08};
	base_animation.Set(_src_pos,4,temp);
	base_animation.loop = true;

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

	if(flipped){sprite.Render(&base_animation, SDL_FLIP_HORIZONTAL);}
	else{sprite.Render(&base_animation);}
}

void Player::HandleEvents(SDL_Event* _event)
{
	if(_event->type == SDL_KEYDOWN){
		switch(_event->key.keysym.sym){
			case SDLK_UP:
				w_up = true;
				break;
			case SDLK_RIGHT:
				w_right = true;
				break;
			case SDLK_DOWN:
				w_down = true;
				break;
			case SDLK_LEFT:
				w_left = true;
				break;
			default:
				break;
		}
	}
	if(_event->type == SDL_KEYUP){
		switch(_event->key.keysym.sym){
			case SDLK_UP:
				w_up = false;
				break;
			case SDLK_RIGHT:
				w_right = false;
				break;
			case SDLK_DOWN:
				w_down = false;
				break;
			case SDLK_LEFT:
				w_left = false;
				break;
			default:
				break;
		}
	}
}

void Player::Update()
{
	if(w_left){
		flipped = true;
		velocity.x -= 0.08;
		if(velocity.x < -(max_velocity.x)){velocity.x = -(max_velocity.x);}
	}
	else{
		if(velocity.x < 0){
			if(velocity.x > -1 && velocity.x < 0){velocity.x = 0;}
			else{velocity.x += 0.72;}
		}
	}
	if(w_right){
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

	if(w_up){
		if(grounded){
			pos_y -= 50;
			grounded = false;
		}
	}
	if(w_down){
		if(!grounded){
			pos_y +=(50 * Timer::delta_time);
		}
	}

	if(!grounded){
		pos_y += (50 * Timer::delta_time);
	}

	pos_x += velocity.x * (100 * Timer::delta_time);

	if(pos_x < 0){
		pos_x = 0;
		velocity.x = 0;
	}

	if(pos_x + width > 380){pos_x = 380 - width;}

	if(w_left || w_right){base_animation.Progress();}
	else{base_animation.Stop();}
	

	printf("vel: %f \n", static_cast<float>(velocity.x));
}

void Player::Destroy()
{

}