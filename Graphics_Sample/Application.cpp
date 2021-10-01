#define _CRTDBG_MAP_ALLOC
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include "Application.h"

bool Application::Init(HINSTANCE hInstance, int32_t winMode)
{
    bool sts = false;

    // メモリーリークを検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Window* window = Window::Instance();

    // ウィンドウクラスの登録
    window->RegisterClass(hInstance, CS_OWNDC, L"Main");

    // ウィンドウの作成
    sts = window->Create(hInstance,
                         WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU,
                         0,
                         L"Main",
                         L"Graphics Sample",
                         false,
                         Vector2Int(960,540));

    // ウィンドウの表示
    window->Show(winMode);

    return sts;
}

int32_t Application::MainLoop()
{
    Window* window = Window::Instance();

    // メインループ
    while (window->ExecMessage())
    {
        
    }

    return window->GetMessage();
}

void Application::Uninit()
{


}
