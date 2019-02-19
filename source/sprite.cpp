

void Sprite::Render()
{
    //Texture Rendering
    if(animation.max_frame_count == -1){
        T_Renderer::RenderTexture(source_sheet->texture, &src_pos, &dst_pos);
        return;
    }

    SDL_Rect temp_pos = animation.Step(src_pos);
    T_Renderer::RenderTexture(source_sheet->texture, &temp_pos, &dst_pos);
}