#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

class BaseEntity
{
public:
	static Texture sprite;
	static void Init();
	static void Deinit();

	int pos_x;
	int pos_y;
	int width;
	int height;

	bool flipped;

	Vector2D velocity;
	Animation base_animation;

	virtual void Create(SDL_Rect _src_pos);
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

};

class Player: public BaseEntity
{
public:
	Animation walking_animation;

	virtual void Create(SDL_Rect _src_pos);
	virtual void Render();
	virtual void Destroy();
};


#endif