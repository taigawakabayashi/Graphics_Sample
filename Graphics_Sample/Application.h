//********************************************************************************************************
// \file   Application.h
// \brief  
// 
// \author wakaa
// \date   2021/10/1
//********************************************************************************************************
#pragma once
#ifndef APP_H
#define APP_H
#include "Window.h"

enum class GRAPGICS
{
    DIRECTX11,
    DIRECTX12,
    OPENGL,
    VULKAN,
};

class Application
{
public:

    bool Init(HINSTANCE hInstance, int32_t winMode);

    int32_t MainLoop();

    HWND GetHandle(){ return m_handle; }

    void Uninit();

private:

    HWND m_handle;              // ウィンドウハンドル

    HINSTANCE m_hInstance;      // アプリケーションインスタンス
};

#endif // !APP_H
