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
#include "Math.h"

class Window 
{
public:
    
    // GetInstance
    static Window* Instance() {

        static Window instance;

        return &instance;
    }

    bool RegisterClass(const HINSTANCE hInstance,
                       const unsigned long style,
                       const wchar_t* className);

    // CreateWindow
    bool Create(const HINSTANCE hInstance,
                const unsigned long style,
                const unsigned long exStyle,
                const wchar_t* className,
                const wchar_t* title,
                const bool fullScreen,
                const Vector2Int size);

    // ShowWindow
    void Show(uint32_t winMode);

    // Execution Message
    bool ExecMessage();

    // Getter
    HWND GetHandle() const;
    long GetMessage() const;

private:

    HWND    m_handle;       // Window Handle
    MSG     m_message;      // Message

};
#endif // WIN_H