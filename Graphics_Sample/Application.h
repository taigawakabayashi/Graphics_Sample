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
#include "SwitchingAPI.h"
#include "Game.h"

class Application
{
public:

    bool Init(HINSTANCE _hInstance, int32_t _winMode);

    int32_t MainLoop();

    HWND GetHandle(){ return m_handle; }

    void Uninit();

private:

    HWND m_handle = nullptr;              // ウィンドウハンドル

    HINSTANCE m_hInstance = nullptr;      // アプリケーションインスタンス

    GraphicsAPI m_useAPI = GraphicsAPI::DIRECTX11;       //
};

#endif // !APP_H
