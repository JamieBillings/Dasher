/*==============================================================================
							Texture Class
==============================================================================*/

void Texture::Load(std::string _location)
{
	int comp = 0;
	uint8_t* pixel_stream = stbi_load(_location.c_str(),&dst_pos.w,&dst_pos.h,nullptr,4);
	SDL_Surface* image;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    	uint32_t rmask = 0xff000000;
    	uint32_t gmask = 0x00ff0000;
    	uint32_t bmask = 0x0000ff00;
    	uint32_t amask = 0x000000ff;
	#else
    	uint32_t rmask = 0x000000ff;
    	uint32_t gmask = 0x0000ff00;
    	uint32_t bmask = 0x00ff0000;
    	uint32_t amask = 0xff000000;
	#endif

	image = SDL_CreateRGBSurface(0,dst_pos.w,dst_pos.h,32,
		rmask, gmask, bmask, amask);

	SDL_LockSurface(image);
	memcpy(image->pixels, pixel_stream, dst_pos.w * 4 * dst_pos.h);
	SDL_UnlockSurface(image);

	if(!image){printf("Failed to Create Image %s\n",SDL_GetError());}
	else{
		texture = SDL_CreateTextureFromSurface(Renderer::renderer, image);
		if(!texture){printf("Failed to Create Texture %s\n",SDL_GetError());}
		else{
			SDL_QueryTexture(texture, NULL, NULL, &dst_pos.w, &dst_pos.h);
			src_pos = dst_pos;
			src_pos.x = 0;
			src_pos.y = 0;
			printf("Texture Created Successfully with size, X: %d Y: %d W: %d H: %d\n",src_pos.x,src_pos.y,src_pos.w,src_pos.h);
		}
	}
	SDL_FreeSurface(image);
}

void Texture::Render()
{
	SDL_Rect true_dst = dst_pos;
	true_dst.x = Camrea::offset_x + (true_dst.x * Renderer::render_scale);
	true_dst.y = Camrea::offset_y + (true_dst.y * Renderer::render_scale);
	true_dst.w *=  Renderer::render_scale;
	true_dst.h *=  Renderer::render_scale;
	SDL_RenderCopy(Renderer::renderer, texture, &src_pos, &true_dst);
}

void Texture::RenderFlip()
{
	SDL_Rect true_dst = dst_pos;
	true_dst.x = Camrea::offset_x + (true_dst.x * Renderer::render_scale);
	true_dst.y = Camrea::offset_y + (true_dst.y * Renderer::render_scale);
	true_dst.w *=  Renderer::render_scale;
	true_dst.h *=  Renderer::render_scale;
	SDL_RenderCopyEx(Renderer::renderer, texture, &src_pos, &true_dst, 0.00, nullptr, SDL_FLIP_HORIZONTAL);
}

void Texture::RenderRotate(double _rotation)
{
	SDL_Rect true_dst = dst_pos;
	true_dst.x = Camrea::offset_x + (true_dst.x * Renderer::render_scale);
	true_dst.y = Camrea::offset_y + (true_dst.y * Renderer::render_scale);
	true_dst.w = true_dst.w * Renderer::render_scale;
	true_dst.h = true_dst.h * Renderer::render_scale;
	SDL_RenderCopyEx(Renderer::renderer, texture, &src_pos, &true_dst, _rotation, nullptr, SDL_FLIP_NONE);
}

void Texture::Render(Animation* _animation)
{
	SDL_Rect true_dst = dst_pos;
	true_dst.x = Camrea::offset_x + (true_dst.x * Renderer::render_scale);
	true_dst.y = Camrea::offset_y + (true_dst.y * Renderer::render_scale);
	true_dst.w *=  Renderer::render_scale;
	true_dst.h *=  Renderer::render_scale;

	SDL_Rect true_src = _animation->base_pos;
	true_src.x = _animation->base_pos.x + _animation->base_pos.w * _animation->current_frame;
	SDL_RenderCopy(Renderer::renderer, texture, &true_src, &true_dst);
}

void Texture::Render(Animation* _animation, SDL_RendererFlip _flip)
{
	SDL_Rect true_dst = dst_pos;
	true_dst.x = Camrea::offset_x + (true_dst.x * Renderer::render_scale);
	true_dst.y = Camrea::offset_y + (true_dst.y * Renderer::render_scale);
	true_dst.w *=  Renderer::render_scale;
	true_dst.h *=  Renderer::render_scale;

	SDL_Rect true_src = _animation->base_pos;
	true_src.x = _animation->base_pos.x + _animation->base_pos.w * _animation->current_frame;
	SDL_RenderCopyEx(Renderer::renderer, texture, &true_src, &true_dst, 0.00, nullptr, _flip);
}

void Texture::Unload()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

/*==============================================================================
							Animation Class
==============================================================================*/

void Animation::Set(SDL_Rect _base_pos, int _key_frames, float* _speed_per_frame)
{
	base_pos = _base_pos;
	key_frames= _key_frames;
	speed_per_frame = static_cast<float*>(malloc(_key_frames*sizeof(float)));
	memcpy(speed_per_frame, _speed_per_frame, key_frames*sizeof(float));
	current_frame = 0;
	counter = 0.0;
}

void Animation::Progress()
{
	counter += Timer::delta_time;
	while(counter > speed_per_frame[current_frame]){
		counter -= speed_per_frame[current_frame];
		if(current_frame == key_frames-1){
			if(loop){current_frame = 0;}
		}
		else{
			current_frame++;
		}
	}
}

void Animation::Stop()
{
	current_frame = 0;
	counter = 0.0;
}