#pragma once
#ifndef GAME_H
#define GAME_H

#include "DirectX11Graphics.h"

namespace Game 
{
    bool Init(HWND hWnd, Vector2Int size);

    void Input(uint64_t deltaTime);
    void Update(uint64_t deltaTime);
    void Draw(uint64_t deltaTime);

    void Uninit();
}


#endif // !GAME_H
