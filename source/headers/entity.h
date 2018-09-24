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

	float jump_height;

	EntityState state;
};

struct Player
{
	
};

namespace Entity
{
	//Static Functions
	void Init();
	void Deinit();

	void Create(BaseEntity _self, SDL_Rect _base_pos);
	void Create(Player _self, SDL_Rect _base_pos);
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

	int jump_height;

	//Change the ENUM Later
	bool flipped = false;
	bool grounded = false;

	Vector2D velocity;
	Vector2D max_velocity;

	Animation base_animation;
	Animation walking_animation;
	Animation jumping_animation;

	//Change to ENUM Later
	bool is_base = false;
	bool is_walking = false;
	bool is_jumping = false;

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