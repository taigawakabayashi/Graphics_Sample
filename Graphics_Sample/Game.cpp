#include "Game.h"

bool Game::Init(HWND hWnd, Vector2Int size)
{
    bool sts = DirectX11::GraphicsMng::GetInstance()->Init(hWnd, size);

    return sts;
}

void Game::Input(uint64_t deltaTime)
{

}

void Game::Update(uint64_t deltaTime)
{

}

void Game::Draw(uint64_t deltaTime)
{
    float col[4] = { 0.0f, 1.0f, 1.0f, 1.0f };

    DirectX11::BeforeRender(col);



    DirectX11::AfterRender();
}

void Game::Uninit()
{
    DirectX11::GraphicsMng::GetInstance()->Uninit();
}
