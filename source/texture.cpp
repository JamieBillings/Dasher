void Texture::LoadTexture(std::string _file)
{
	//Preparing Pixel Data
    uint8_t* image_data;
    image_data = stbi_load(_file.c_str(), &width, &height, nullptr, 4);
    SDL_Surface* temp_surface;

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

    if(image_data == nullptr){
        std::string error_message =  "Failed to Load Image data ";
        error_message +=  _file;
        OS::CreateErrorWindow(error_message, error_level::error);
        goto endfunction;
    }

    temp_surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
    if(temp_surface == nullptr){
        printf("Unable to Create Surface %s\n", SDL_GetError());
        goto endfunction;
    }

    SDL_LockSurface(temp_surface);
    memcpy(temp_surface->pixels, image_data, width * height * 4);
    SDL_UnlockSurface(temp_surface);
    texture = SDL_CreateTextureFromSurface(T_Renderer::renderer, temp_surface);

    if(texture == nullptr){
        printf("Unable to Create Texture %s\n", SDL_GetError());
    }

    endfunction:
    SDL_FreeSurface(temp_surface);
    stbi_image_free(image_data);
}

void Texture::FreeImage()
{
    SDL_DestroyTexture(texture);
}

SDL_Rect Animation::Step(SDL_Rect _src_pos)
{
    time += T_FPSTimer::delta_time;
    while(time > speed){
        time -= speed;
        if(frame_count < max_frame_count){frame_count++;}
        else{
            if(loop){frame_count = 0;}
        }
    }

    SDL_Rect temp_pos;
    temp_pos = _src_pos;
    temp_pos.x += frame_count * frame_width;

    return temp_pos;
}
