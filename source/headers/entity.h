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
}

enum Identifer
{
	is_player,
 	is_unknown_enemy_type
}

enum KeyHeld
{
	
}

struct BaseEntity
{
	static Texture sprite;

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

	EntityState state;
};

namespace Entity
{
	namespace Player
	{

	}
	//Static Functions
	void Init();
	void Deinit();

	//base entity functions
	void Create(BaseEntity _self, SDL_Rect _base_pos);
	void Update();
	void Render();
	void Destroy();
}

class BaseEntity
{
public:
	static Texture sprite;
	static void Init();
	static void Deinit();

	float pos_x;
	float pos_y;
	int width;
	int height;

	Vector2D vector;

	static float map_offset;

	Animation base_animation;
	Animation walking_animation;
	Animation jumping_animation;

	virtual void Create(SDL_Rect _src_pos);
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	void Jump();

};

class Player: public BaseEntity
{
public:
	bool walk_up;
	bool walk_right;
	bool walk_down;
	bool walk_left;

	virtual void Create(SDL_Rect _src_pos);
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
	void HandleEvents(SDL_Event* _event);
	void CheckMapBound();
};


#endif