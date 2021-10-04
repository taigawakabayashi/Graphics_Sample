#pragma once
#ifndef GAME_H
#define GAME_H

#include "DirectX11Graphics.h"

class Game
{
public:

    static bool Init(HWND hWnd, Vector2Int size);

    static void Input(uint64_t deltaTime);
    static void Update(uint64_t deltaTime);
    static void Draw(uint64_t deltaTime);

    static void Uninit();

private:

};
#endif // !GAME_H
