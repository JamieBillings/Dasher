namespace Init
{
void Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("Error Initalising SDL2\n");
	}
}

void Deinit()
{
	SDL_Quit();
}

}

namespace Error
{

//void PrintError(std::string _error){printf(_error);}


}