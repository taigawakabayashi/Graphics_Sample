#include <Windows.h>
#include <tchar.h>
#include "Application.h"

int APIENTRY WinMain(_In_     HINSTANCE  _hInst,
                     _In_opt_ HINSTANCE,
                     _In_     LPSTR,
                     _In_     int		 _winMode) 
{
    //------------------------------
    Application app;

    app.Init(_hInst, _winMode);

    int ret = app.MainLoop();

    app.Uninit();

    return ret;
}
