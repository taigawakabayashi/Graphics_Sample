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

class Application
{
public:

    bool Init(HINSTANCE hInstance,int32_t winMode);

    int32_t MainLoop();

    void Uninit();

private:
};

#endif // !APP_H
