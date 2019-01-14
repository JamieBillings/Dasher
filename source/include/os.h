#ifndef __OS__DASHER
#define __OS__DASHER

#if defined(_WIN32)
    #define OS_WINDOWS
#elif defined(_WIN64)
    #define OS_WINDOWS
#elif defined(__linux__)
    #define OS_LINUX
#else
    #define OS_UNKNOWN
#endif

enum error_level
{
    debug   = 0,    //Error will appear in console but not as a window.
    warning = 1,    //Error will open a window but allow the game to continue.
    error   = 2     //Error will stop the game from running.
};

namespace OSWindows
{

void Setup();
void CreateErrorWindow();

}

namespace OSLinux
{

void Setup();
void CreateErrorWindow();

}

#if defined(OS_WINDOWS)
#include <windows.h>
namespace OS
{
    HWND    hwnd;
    HANDLE  handle;

    void Setup(){OSWindows::Setup();}
    void CreateErrorWindow(){OSWindows::CreateErrorWindow();}
}


#elif defined(OS_LINUX)
namespace OS
{
    void Setup(){OSLinux::Setup();}
    void CreateErrorWindow(){OSLinux::CreateErrorWindow();}
}

#elif defined(OS_UNKNOWN)
namespace OS
{
    void Setup(){return;}
    void CreateErrorWindow(){return;}
}
#endif










#endif