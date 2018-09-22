#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Animation
{
public:
	SDL_Rect base_pos;
	int key_frames;
	int current_frame; //this should be the only constantly changing value in Animation
	float* speed_per_frame;

	float counter;

	bool loop;

	void Set(SDL_Rect _base_pos, int _key_frames, float* _speed_per_frame);
	void Progress();
	void Stop();
	void Delete();
};

class Texture
{
public:
	SDL_Texture* texture;

	SDL_Rect src_pos;
	SDL_Rect dst_pos;

	void Load(std::string _location);

	void Render();
	void Render(Animation* _animation);
	void Render(Animation* _animation, SDL_RendererFlip _flip);
	void RenderRotate(double _dir);
	void RenderFlip();
	void RenderFlip(Animation* _animation);
	void RenderRotate(double _dir, Animation* _animation);
	

	void Unload();
};

#endif