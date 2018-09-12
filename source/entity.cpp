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

}

void BaseEntity::Render()
{

}

void BaseEntity::Destroy()
{

}

void Player::Create(SDL_Rect _src_pos)
{
	float temp[1] = {0.00};
	base_animation.Set(_src_pos,1,temp);

	pos_x = 320;
	pos_y = 240;
	width = _src_pos.w;
	height = _src_pos.h;
}

void Player::Render()
{
	sprite.dst_pos = {pos_x, pos_y, width, height};
	sprite.Render(&base_animation);

	if(flipped){sprite.Render(&base_animation, SDL_FLIP_HORIZONTAL);}
	else{sprite.Render(&base_animation);}
}

void Player::Destroy()
{

}