#include "headers\\entity.h"

Texture BaseEntity::sprite;

void BaseEntity::Init()
{
	sprite.Load("Dev\\Images\\spritesheet.png");
}

void BaseEntity::Deinit()
{
	sprite.Unload();
}

void BaseEntity::Create(SDL_Rect _src_pos)
{
	float temp[1] = {0.00};
	base_animation.Set(_src_pos,1,temp);

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
	float temp[1] = {0.00};
	base_animation.Set(_src_pos,1,temp);

	pos_x = 320;
	pos_y = 322 - 64;
	width = _src_pos.w;
	height = _src_pos.h;
}

void Player::Render()
{
	int temp_x = static_cast<int>(pos_x);
	int temp_y = static_cast<int>(pos_y);
	sprite.dst_pos = {temp_x, temp_y, width, height};
	sprite.Render(&base_animation);

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
		if(pos_x < 0){pos_x = 0;}	
		else{pos_x -= (100 * Timer::delta_time);}
	}
	if(w_right){
		flipped = false;
		if(pos_x + width > 380){pos_x = 380 - width;}
		else{pos_x += (100 * Timer::delta_time);}
	}
	if(w_up){
		if(grounded){
			pos_y -= 50;
			grounded = false;
		}
	}
	if(w_down){
		if(!grounded){
			pos_y += (50 * Timer::delta_time);
		}
	}
}

void Player::Destroy()
{

}