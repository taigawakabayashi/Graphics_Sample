//********************************************************************************************************
// \file   Window.h
// \brief  
// 
// \author wakaa
// \date   2021/10/1
//********************************************************************************************************
#pragma once
#ifndef WIN_H
#define WIN_H

#include <Windows.h>
#include <Utility/Math.h>

class Window 
{
public:

    bool RegisterClass(const HINSTANCE _hInstance,
                       const unsigned long _style,
                       const wchar_t* _pClassName);

    // CreateWindow
    bool Create(const HINSTANCE _hInstance,
                const unsigned long _style,
                const unsigned long _exStyle,
                const wchar_t* _pClassName,
                const wchar_t* _pTitle,
                const bool _fullScreen,
                const Vector2Int _size);

    // ShowWindow
    void Show(uint32_t _winMode);

    // GetHandle
    HWND GetHandle() const;

private:

    HWND    m_handle = nullptr;       // Window Handle
};
#endif // WIN_H