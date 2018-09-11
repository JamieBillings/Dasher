namespace Game
{
	bool Event(SDL_Event* event)
	{
		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT){return false;}

		}

		return true;
	}

	void Init()
	{

	}

	void GameLoop()
	{

	}

	void Render()
	{
		SDL_SetRenderDrawColor(Renderer::renderer, 0, 0, 0, 255);

		Renderer::ClearRenderer();

		//Render Code here

		Renderer::PresentRenderer();
	}

	void Destroy()
	{
		Renderer::DestroyRenderer();
		Window::DestroyWindow();
	}
}