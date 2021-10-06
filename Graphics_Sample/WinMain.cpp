#include <Windows.h>
#include <tchar.h>
#include "Application.h"

int APIENTRY WinMain(_In_     HINSTANCE  h_hInst,
                     _In_opt_ HINSTANCE,
                     _In_     LPSTR,
                     _In_     int		 h_nWinMode) 
{
    //------------------------------
    Application app;

    app.Init(h_hInst, h_nWinMode);

    int ret = app.MainLoop();

    app.Uninit();

    return ret;
}
