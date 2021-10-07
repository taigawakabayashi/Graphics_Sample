//********************************************************************************************************
// \file   Window.cpp
// \brief  
// 
// \author wakaa
// \date   2021/10/1
//********************************************************************************************************
#include "Window.h"

static LRESULT APIENTRY WindowProc(HWND _handle, UINT _message, WPARAM _wParam, LPARAM _lParam) {

    switch (_message)
    {
        // キー押下
    case WM_KEYDOWN:

        switch (_wParam) {

        case VK_ESCAPE:

            DestroyWindow(_handle);

            //PostQuitMessage(0);

            break;

        default:

            return DefWindowProc(_handle, _message, _wParam, _lParam);
        }
        return 0;

        // ×
    case WM_CLOSE:

        PostQuitMessage(0);

        return 0;

        // ウインドウ解放
    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;

    default:

        break;
    }
        return DefWindowProc(_handle, _message, _wParam, _lParam);
}

//*****************************************
// RegisterClass.
// 
// \param hInstance
// \param style
// \param className
// \return true on success
//*****************************************
bool Window::RegisterClass(const HINSTANCE _hInstance, const unsigned long _style, const wchar_t* _pClassName)
{
    WNDCLASSEX WndClassEx;
    WndClassEx.cbSize = sizeof(WNDCLASSEX);
    WndClassEx.style = _style;
    WndClassEx.lpfnWndProc = WindowProc;
    WndClassEx.cbClsExtra = 0L;
    WndClassEx.cbWndExtra = 0L;
    WndClassEx.hInstance = _hInstance;
    WndClassEx.hIcon = nullptr;
    WndClassEx.hCursor = nullptr;
    WndClassEx.hbrBackground = nullptr;
    WndClassEx.lpszMenuName = nullptr;
    WndClassEx.lpszClassName = _pClassName;
    WndClassEx.hIconSm = NULL;

    if (!RegisterClassEx(&WndClassEx))
    {
        MessageBox(NULL, L"RegisterClassEx", L"Error!", MB_OK);
        return false;
    }

    return true;
}

//*****************************************
// Create.
// 
// @param hInstance
// @param style
// @param exStyle
// @param className
// @param title
// @param fullScreen
// @param size
// 
// @return true on success
//*****************************************
bool Window::Create(const HINSTANCE _hInstance,
                    const unsigned long _style, 
                    const unsigned long _exStyle, 
                    const wchar_t* _pClassName,
                    const wchar_t* _pTitle,
                    const bool _fullScreen, 
                    const Vector2Int _size)
{
    if (_fullScreen) {

        m_handle = CreateWindowEx(
            _exStyle,
            _pClassName,					// ウィンドウクラスの名前
            _pTitle,						// タイトル
            WS_POPUP,						// ウィンドウスタイル
            0, 0,							// ウィンドウ位置 縦, 横
            _size.x, _size.y,				// ウィンドウサイズ
            nullptr,						// 親ウィンドウなし
            nullptr,						// メニューなし
            _hInstance,						// インスタンスハンドル
            nullptr);						// 追加引数なし
    }
    else {

        RECT rc;

        SetRect(&rc, 0, 0, _size.x, _size.y);
        AdjustWindowRectEx(&rc, _style, FALSE, _exStyle);

        m_handle = CreateWindowEx(
            _exStyle,
            _pClassName,									// ウィンドウクラスの名前
            _pTitle,										// タイトル
            //WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU,	// ウィンドウスタイル
            _style,		                                    // ウィンドウスタイル
            0,0,											// ウィンドウ位置 縦, 横
            rc.right - rc.left, rc.bottom - rc.top,			// ウィンドウサイズ
            HWND_DESKTOP,									// 親ウィンドウなし
            nullptr,										// メニューなし
            _hInstance,										// インスタンスハンドル
            nullptr);										// 追加引数なし

        // ウィンドウの位置を再調整
        SetWindowPos(m_handle, 
                     nullptr, 
                     GetSystemMetrics(SM_CXSCREEN) / 2 - _size.x / 2, 
                     GetSystemMetrics(SM_CYSCREEN) / 2 - _size.y / 2, 
                     0, 0, 
                     SWP_NOSIZE | SWP_NOZORDER);
    }

    if (!m_handle) {

        MessageBox(nullptr, L"CreateWindow Error", L"error", MB_OK);

        return false;
    }

    return true;
}

//*****************************************
// Show.
// 
// \param winMode
//*****************************************
void Window::Show(uint32_t _winMode)
{
    ShowWindow(m_handle, _winMode);

    UpdateWindow(m_handle);
}

//*****************************************
// GetHandle.
// 
// \return window handle
//*****************************************
HWND Window::GetHandle() const
{
    return m_handle;
}
