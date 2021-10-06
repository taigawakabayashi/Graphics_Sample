#define _CRTDBG_MAP_ALLOC
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "Application.h"
#include "Game.h"
#include "Timer.h"

bool Application::Init(HINSTANCE hInstance, int32_t winMode)
{
    bool sts = false;

    // メモリーリークを検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ////コンソールを作成
    //AllocConsole();

    //FILE* m_fp = nullptr; 

    //// 標準出力の割り当て
    //freopen_s(&m_fp, "CON", "w", stdout);
    //freopen_s(&m_fp, "CON", "r", stdin);

    Window window;

    // ウィンドウクラスの登録
    window.RegisterClass(hInstance, CS_OWNDC, L"Main");

    // ウィンドウの作成
    sts = window.Create(hInstance,
                        WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU,
                        0,
                        L"Main",
                        L"Graphics Sample",
                        false,
                        Vector2Int(960,540));

    // ウィンドウの表示
    window.Show(winMode);

    // ウィンドウハンドルを保存
    m_handle = window.GetHandle();

    // アプリケーションインスタンスを保存
    m_hInstance = hInstance;

    return sts;
}

int32_t Application::MainLoop()
{
    MSG message = {};

    uint64_t deltaTime = 0;

    // 初期化
    Game::Init(m_handle, Vector2Int(960, 540));

    // メインループ
    while (WM_QUIT != message.message)
    {
        // メッセージがある場合はそちらの処理を優先
        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&message);     // メッセージの変換
            DispatchMessage(&message);      // メッセージの送出
        }
        else 
        {
            // CurrentTime セット & DeltaTime を計算
            Timer::SetStart();

            // DeltaTime 取得
            deltaTime = Timer::GetDeltaTIme();

            // ↓メイン処理
            Game::Input(deltaTime);     // 入力
            Game::Update(deltaTime);    // 更新
            Game::Draw(deltaTime);      // 描画
            // ↑

            // LastTime セット
            Timer::SetEnd();

            //printf("%dns    %f\n", Timer::GetDeltaTIme(), Timer::GetFPS());

            // 指定したFPS以上になった場合にスレッドを一時停止する
            std::this_thread::sleep_for(Timer::GetSleepTImeForFPS(60));
        }
    }

    // 終了処理
    Game::Uninit();

    return message.message;
}

void Application::Uninit()
{


}
