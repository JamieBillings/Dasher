#include "headers\\entity.h"

void BaseEntity::Init()
{
	
}

void BaseEntity::Deinit()
{
	
}

void BaseEntity::Create(SDL_Rect _src_pos)
{
	float temp[1] = {0.00};
	base_animation.Create(_src_pos,1,temp);
	
}