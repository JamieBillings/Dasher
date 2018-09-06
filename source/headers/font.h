#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

/*	Note:

	This file is to be used with AngleCodes Bitmap Font Generator BMFONT
	http://www.angelcode.com/products/bmfont/
	http://www.angelcode.com/products/bmfont/documentation.html
*/


class Character
{
public:
	SDL_Rect src_pos;
	int offset_x;
	int offset_y;
	int x_advanced;

	Character();
	~Character();

	void Render(SDL_Rect* _pos, Texture* _texture);
};

class Font
{
public:
	int line_height;
	int base;
	int scale_w;
	int scale_h;

	int character_count;
	Character* font_characters;

	Texture font_texture;

	void Create(std::string _location);
	void Render(std::string _input, SDL_Rect* _pos);
	void Destroy();
};

namespace FontTools
{
	Font default_font;
	void Init();
	void Destroy();
}


#endif