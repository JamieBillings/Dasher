

namespace OSWindows
{



void Setup(SDL_Window* _window)
{
    SDL_SysWMinfo system_info;

    if(!SDL_GetWindowWMInfo(_window, &system_info)){
        printf("Error Getting HWND, All Errors will be in console \n");
        return;
    }

    OS::self = system_info.info.win.window;
}


void CreateErrorWindow(std::string _message, error_level _level)
{
    switch(_level){
        case error:
            MessageBoxA(OS::self, _message.c_str(), "Error", MB_OK);
            Global::running = false;
            break;

        case warning:
            MessageBoxA(OS::self, _message.c_str(), "Warning", MB_OK);
            break;

        default:
            printf("%s\n", _message.c_str());
            break;
    }
}

}

namespace OSLinux
{

void Setup()
{

}

void CreateErrorWindow()
{

}

}