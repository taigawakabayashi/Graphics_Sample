//********************************************************************************************************
// \file   Window.cpp
// \brief  
// 
// \author wakaa
// \date   2021/10/1
//********************************************************************************************************
#include "Window.h"

static LRESULT APIENTRY WindowProc(HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam) {

    switch (h_Message)
    {
        // �L�[����
    case WM_KEYDOWN:

        switch (h_WParam) {

        case VK_ESCAPE:

            DestroyWindow(h_Handle);

            break;

        default:

            return DefWindowProc(h_Handle, h_Message, h_WParam, h_LParam);
        }
        return 0;

        // �~
    case WM_CLOSE:

        PostQuitMessage(0);

        return 0;

        // �E�C���h�E���
    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;

    default:

        return DefWindowProc(h_Handle, h_Message, h_WParam, h_LParam);
    }
}

//*****************************************
// RegisterClass.
// 
// \param hInstance
// \param style
// \param className
// \return true on success
//*****************************************
bool Window::RegisterClass(const HINSTANCE hInstance, const unsigned long style, const wchar_t* className)
{
    WNDCLASSEX WndClassEx;
    WndClassEx.cbSize = sizeof(WNDCLASSEX);
    WndClassEx.style = style;
    WndClassEx.lpfnWndProc = WindowProc;
    WndClassEx.cbClsExtra = 0L;
    WndClassEx.cbWndExtra = 0L;
    WndClassEx.hInstance = hInstance;
    WndClassEx.hIcon = nullptr;
    WndClassEx.hCursor = nullptr;
    WndClassEx.hbrBackground = nullptr;
    WndClassEx.lpszMenuName = nullptr;
    WndClassEx.lpszClassName = className;
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
bool Window::Create(const HINSTANCE hInstance,
                    const unsigned long style, 
                    const unsigned long exStyle, 
                    const wchar_t* className,
                    const wchar_t* title,
                    const bool fullScreen, 
                    const Vector2Int size)
{
    if (fullScreen) {

        m_handle = CreateWindowEx(
            exStyle,
            className,						// �E�B���h�E�N���X�̖��O
            title,							// �^�C�g��
            WS_POPUP,						// �E�B���h�E�X�^�C��
            0, 0,							// �E�B���h�E�ʒu �c, ��
            size.x, size.y,					// �E�B���h�E�T�C�Y
            nullptr,						// �e�E�B���h�E�Ȃ�
            nullptr,						// ���j���[�Ȃ�
            hInstance,						// �C���X�^���X�n���h��
            nullptr);						// �ǉ������Ȃ�
    }
    else {

        RECT rc;

        SetRect(&rc, 0, 0, size.x, size.y);
        AdjustWindowRectEx(&rc, style, FALSE, exStyle);

        m_handle = CreateWindowEx(
            exStyle,
            className,										// �E�B���h�E�N���X�̖��O
            title,											// �^�C�g��
            //WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU,	// �E�B���h�E�X�^�C��
            style,		                                    // �E�B���h�E�X�^�C��
            0,0,											// �E�B���h�E�ʒu �c, ��
            rc.right - rc.left, rc.bottom - rc.top,			// �E�B���h�E�T�C�Y
            HWND_DESKTOP,									// �e�E�B���h�E�Ȃ�
            nullptr,										// ���j���[�Ȃ�
            hInstance,										// �C���X�^���X�n���h��
            nullptr);										// �ǉ������Ȃ�

        // �E�B���h�E�̈ʒu���Ē���
        SetWindowPos(m_handle, 
                     nullptr, 
                     GetSystemMetrics(SM_CXSCREEN) / 2 - size.x / 2, 
                     GetSystemMetrics(SM_CYSCREEN) / 2 - size.y / 2, 
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
void Window::Show(uint32_t winMode)
{
    ShowWindow(m_handle, winMode);

    UpdateWindow(m_handle);
}

//*****************************************
// ExecMessage.
// 
// \return true on success
//*****************************************
bool Window::ExecMessage()
{
    // ���b�Z�[�W�m�F
    while (PeekMessage(&m_message, m_handle, 0, 0, PM_NOREMOVE))
    {
        // ���b�Z�[�W�Ȃ�
        if (!(::GetMessage(&m_message, m_handle, 0, 0)))
            return false;

        TranslateMessage(&m_message);	// �L�[���b�Z�[�W�̕ϊ�
        DispatchMessage(&m_message);	// ���b�Z�[�W�̑��o
    }

    return true;
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

//*****************************************
// GetMessage.
// 
// \return message
//*****************************************
long Window::GetMessage() const
{
    return m_message.message;
}