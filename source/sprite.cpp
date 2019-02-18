void Sprite::Render()
{
    SDL_Rect temp_pos;
    temp_pos = src_pos;

    T_Renderer::RenderTexture(source_sheet->texture, &src_pos, &dst_pos);

    //Animation
}