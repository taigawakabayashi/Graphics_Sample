#pragma once
#ifndef GAME_H
#define GAME_H

#include <DirectX11/DirectX11_GraphicsManager.h>
#include <DirectX12/DirectX12_GraphicsManager.h>

namespace Rnderer 
{
    bool Init(HWND _hWnd, Vector2Int _size);

    void Input(uint64_t _deltaTime);
    void Update(uint64_t _deltaTime);
    void Draw(uint64_t _deltaTime);

    void Uninit();
}


#endif // !GAME_H
