#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

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

	bool flipped = false;
	bool grounded = false;

	Vector2D velocity;
	Vector2D max_velocity;

	Animation base_animation;

	virtual void Create(SDL_Rect _src_pos);
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	void Jump();

};

class Player: public BaseEntity
{
public:
	Animation walking_animation;

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