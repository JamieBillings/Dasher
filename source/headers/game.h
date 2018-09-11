#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

namespace Game
{
	bool Event(SDL_Event* event);
	void Init();
	void GameLoop();
	void Render();
	void Destroy();
}

#endif