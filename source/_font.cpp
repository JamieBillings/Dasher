/*

*/
void Character::Render(SDL_Rect* _pos, Texture* _texture)
{
	_texture->dst_pos = *_pos;
	_texture->dst_pos.y += offset_y;
	_texture->dst_pos.w = src_pos.w + _pos->w;
	_texture->dst_pos.h = src_pos.h + _pos->h;
	_texture->src_pos = src_pos;
	_texture->Render();
}

/*

*/

void Font::Create(std::string _location)
{
	std::ifstream font_file;

	font_file.open(_location + ".fnt", std::ios::binary);
	font_texture.Load(_location + ".png");

	if(font_file.is_open()){

		int size;
		char* memblock;

		font_file.seekg(0, font_file.end);
		size = font_file.tellg();
		font_file.seekg(0, font_file.beg);
		memblock = static_cast<char*>(malloc(size));
		font_file.read(static_cast<char*>(memblock), size);


		int32_t block_1_size = *reinterpret_cast<uint32_t*>(&memblock[5]);
		int32_t block_2_size = *reinterpret_cast<uint32_t*>(&memblock[block_1_size + 10]);
		int32_t block_3_size = *reinterpret_cast<uint32_t*>(&memblock[block_1_size + block_2_size + 15]);
		int32_t block_4_size = *reinterpret_cast<uint32_t*>(&memblock[block_1_size + block_2_size + block_3_size + 20]);
		int32_t block_5_size = *reinterpret_cast<uint32_t*>(&memblock[block_1_size + block_2_size + block_3_size + block_4_size + 25]);
		
		printf("Size of block_1: %u \n", block_1_size);
		printf("Size of block_2: %u \n", block_2_size);
		printf("Size of block_3: %u \n", block_3_size);
		printf("Size of block_4: %u \n", block_4_size);
		printf("Size of block_5: %u \n", block_5_size);

		//Getting the common settings
		int32_t offset = block_1_size + 14;

		line_height = *reinterpret_cast<uint16_t*>(&memblock[offset]);
		offset+=2;
		base = *reinterpret_cast<uint16_t*>(&memblock[offset]);
		offset+=2;
		scale_w = *reinterpret_cast<uint16_t*>(&memblock[offset]);
		offset+=2;
		scale_h = *reinterpret_cast<uint16_t*>(&memblock[offset]);

		//Getting the Chracter Data
		offset = block_1_size + block_2_size + block_3_size + 24;

		printf("Amount of Characters [%u]\n", block_4_size / 20);

		int character_set_offset = *reinterpret_cast<uint32_t*>(&memblock[offset]);

		if(character_set_offset + (block_4_size/20) > 128){
			font_characters = static_cast<Character*>(malloc(character_set_offset + (block_4_size/20)));
			character_count = character_set_offset + block_4_size/20;
		}else{
			font_characters = static_cast<Character*>(malloc(128));
			character_count = 128;
		}

		int counter = 0;
		while(counter < block_4_size){
			int id = *reinterpret_cast<uint32_t*>(&memblock[offset + counter]);
			counter += 4;
			font_characters[id].src_pos.x = *reinterpret_cast<uint16_t*>(&memblock[offset + counter]);
			counter += 2;
			font_characters[id].src_pos.y = *reinterpret_cast<uint16_t*>(&memblock[offset + counter]);
			counter += 2; 
			font_characters[id].src_pos.w = *reinterpret_cast<uint16_t*>(&memblock[offset + counter]);
			counter += 2;
			font_characters[id].src_pos.h = *reinterpret_cast<uint16_t*>(&memblock[offset + counter]);
			counter += 2;
			font_characters[id].offset_x = *reinterpret_cast<uint16_t*>(&memblock[offset + counter]);
			counter += 2;
			font_characters[id].offset_y = *reinterpret_cast<uint16_t*>(&memblock[offset + counter]);
			counter += 2;
			font_characters[id].x_advanced = *reinterpret_cast<uint16_t*>(&memblock[offset + counter]);

			counter += 4;
			printf("Found ID: %i [%c] | Src [%i][%i][%i][%i] \n", id, static_cast<char>(id),
				font_characters[id].src_pos.x,
				font_characters[id].src_pos.y,
				font_characters[id].src_pos.w,
				font_characters[id].src_pos.h);
		}

		font_file.close();
	}
	else{printf("Failed to Open File \n");}
}

void Font::Render(std::string _input, SDL_Rect* dst)
{
	SDL_Rect temp = {dst->x, dst->y, dst->w, dst->h};
	for(uint32_t i = 0; i < _input.length(); i++){
		if(_input.at(i) == '\n'){
			temp.x = dst->x;
			temp.y += line_height + dst->h;
			printf("Tempy = %d\n", temp.y);
			printf("Line Height: %d\n", line_height);
		}
		else if(_input.at(i) == '\t'){
			temp.x += (font_characters[32].x_advanced + dst->w) * 5;
			
		}
		else{
			font_characters[static_cast<uint8_t>(_input.at(i))].Render(&temp, &font_texture);
			temp.x += font_characters[static_cast<uint8_t>(_input.at(i))].x_advanced + dst->w;
		}
	}
}

void Font::Destroy()
{
	free(font_characters);
}

namespace FontTools{

void Init()
{
	default_font.Create("data\\Fonts\\Impact");
}

void Destroy()
{

}

}