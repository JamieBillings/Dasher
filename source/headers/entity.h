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

	int jump_height;

	bool flipped = false;
	bool grounded = false;

	Vector2D velocity;
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

	bool w_up;
	bool w_right;
	bool w_down;
	bool w_left;

	virtual void Create(SDL_Rect _src_pos);
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
	void HandleEvents(SDL_Event* _event);
};


#endif