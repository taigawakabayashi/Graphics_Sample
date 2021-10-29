#define _CRTDBG_MAP_ALLOC
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "Application.h"
#include "Timer.h"
#include "GHI/GHI_Renderer.h"
#include "DirectX12/DirectX12_Renderer.h"

#pragma comment(lib, "winmm.lib")

bool Application::Init(HINSTANCE _hInstance, int32_t _winMode)
{
	bool sts = false;

	m_useAPI = GraphicsAPI::DIRECTX12;

	wchar_t* Title = nullptr;

	switch (m_useAPI)
	{
	case GraphicsAPI::DIRECTX11:
	{

		wchar_t title[] = L"Graphics Sample DirectX11";

		Title = title;

		break;
	}
	case GraphicsAPI::DIRECTX12:
	{
		wchar_t title[] = L"Graphics Sample DirectX12";

		Title = title;

		break;
	}
	case GraphicsAPI::OPENGL:
	{
		wchar_t title[] = L"Graphics Sample OpenGL";

		Title = title;
		break;
	}
	case GraphicsAPI::VULKAN:
	{
		wchar_t title[] = L"Graphics Sample Vulkan";

		Title = title;

		break;
	}
	}

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
	window.RegisterClass(_hInstance, CS_OWNDC, L"Main");

	// ウィンドウの作成
	sts = window.Create(_hInstance,
						WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU,
						0,
						L"Main",
						Title,
						false,
						Vector2Int(960,540));

	// ウィンドウの表示
	window.Show(_winMode);

	// ウィンドウハンドルを保存
	m_handle = window.GetHandle();

	// アプリケーションインスタンスを保存
	m_hInstance = _hInstance;

	return sts;
}

int32_t Application::MainLoop()
{
	MSG message = {};

	uint64_t deltaTime = 0;
	wchar_t fpsCounter[256] = L"";

	Timer timer(60);
	timer.SetStart();

	GHI::GHI_Renderer* renderer = new DirectX12::DX12_Renderer;
	
	renderer->Init(m_handle, Vector2(960.0f, 540.0f));

	// 初期化
	//Render::Init(m_handle, Vector2Int(960, 540), m_useAPI);

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
			// LastTime セット
			timer.SetEnd();

			if (!timer.OverTime()) 
			{
				for (int i = 0; i < 10; ++i) 
				{
					_mm_pause();
				}
			}
			else
			{
				deltaTime = timer.GetDeltaTime();

				float col[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

				// ↓メイン処理
				renderer->BeforeRender(col);
				
				renderer->AfterRender();
				
				//Render::Input(deltaTime);     // 入力
				//Render::Update(deltaTime);    // 更新
				//Render::Draw(deltaTime);      // 描画
				// ↑

				/*swprintf_s(fpsCounter, 256, L"FPS:%.1f", timer.GetFPS());

				SetWindowText(m_handle, fpsCounter);*/

				// CurrentTime セット
				timer.SetStart();
			}

		}
	}

	// 終了処理
	//Render::Uninit();

	delete renderer;

	return message.message;
}

void Application::Uninit()
{


}
