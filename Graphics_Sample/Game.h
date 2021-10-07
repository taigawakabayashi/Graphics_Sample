#pragma once
#ifndef GAME_H
#define GAME_H

#include <DirectX11/DirectX11_GraphicsManager.h>

namespace Game 
{
    bool Init(HWND _hWnd, Vector2Int _size);

    void Input(uint64_t _deltaTime);
    void Update(uint64_t _deltaTime);
    void Draw(uint64_t _deltaTime);

    void Uninit();
}


#endif // !GAME_H
