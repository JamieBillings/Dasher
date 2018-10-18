#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
//CLEAN UP
//Change to Struct System with void* entity List

enum EntityState
{
	is_grounded = 1,
	is_flipped 	= 2,
	is_still 	= 4,
	is_walking 	= 8,
	is_jumping 	= 16
};

enum EntityIdentifier
{
	is_player 	= 1,
 	is_unknown 	= 128
};

enum KeyHeld
{
	jump_up			=   1,
	walk_right		=   2,
	dive_down		=   4,
	walk_left		=   8,

	attack_up		=  16,
	attack_right	=  32,
	attack_down		=  64,
	attack_left		= 128
};

struct EntityStruct
{	
	float pos_x;
	float pos_y;
	int width;
	int height;

	Vector2D velocity;
	Vector2D max_velocity;

	Animation base_animation;
	Animation walking_animation;
	Animation jumping_animation;
	Animation attacking_animation;
	Animation hurt_animation;

	float jump_height;

	int state;
	int identifier;
};

namespace Entity
{
	

	int key_held;

	namespace Private
	{
		static Texture sprite;
	}
	//Static Functions
	void Init();
	void Deinit();

	//base entity functions
	void Create(EntityStruct* _self, SDL_Rect _base_pos);
	EntityStruct CreateBlankEntity();
	void Update(EntityStruct* _self);
	void Render(EntityStruct* _self);
	void Destroy(EntityStruct* _self);

	//player only entity functions
	void HandleKeyEvents(SDL_Event _event);
	void Movement();
}

#endif