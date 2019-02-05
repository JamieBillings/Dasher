
///@@FINISH
void Texture::LoadTextureFromImage(std::string _file)
{
    uint8* pixel_data;
    pixel_data = stbi_load(_file.c_string, &width, &height, nullptr, 4);

    texture = SDL_CreateTexture(T_Renderer::renderer, SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, width, height);

    SDL_LockTexture(texture, NULL, )
}