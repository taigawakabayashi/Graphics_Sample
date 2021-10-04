#define _CRTDBG_MAP_ALLOC
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "Application.h"
#include "Game.h"

bool Application::Init(HINSTANCE hInstance, int32_t winMode)
{
    bool sts = false;

    // メモリーリークを検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //AllocConsole();

    //FILE* m_fp = nullptr; 

    //// 標準出力の割り当て
    //freopen_s(&m_fp, "CON", "w", stdout);
    //freopen_s(&m_fp, "CON", "r", stdin);

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

    m_handle = window->GetHandle();

    return sts;
}

int32_t Application::MainLoop()
{
    Window* window = Window::Instance();

    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point lastTime = std::chrono::system_clock::now();

    Game::Init(m_handle, Vector2Int(960, 540));

    // メインループ
    while (window->ExecMessage())
    {
        currentTime = std::chrono::system_clock::now();
        
        uint64_t deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

        lastTime = currentTime;

        // ↓メイン処理
        Game::Input(deltaTime);
        Game::Update(deltaTime);
        Game::Draw(deltaTime);
        // ↑

        int64_t sleepTime = (1000 / 60) - deltaTime;

        //printf("%d\n", deltaTime);

        if (sleepTime > 0) {

            float sleep = sleepTime / 1000.0f;

            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleep)));
        }
    }

    return window->GetMessage();
}

void Application::Uninit()
{


}
