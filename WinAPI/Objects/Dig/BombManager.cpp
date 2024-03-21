#include "Framework.h"

BombManager::BombManager()
{
    hBrush = CreateSolidBrush(MAGENTA);
    hPen = CreatePen(PS_SOLID, 1, MAGENTA);

    CreateObjects("Bomb", 10);
}

BombManager::~BombManager()
{
    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void BombManager::Plant(const Vector2& pos)
{
    Bomb* bomb = (Bomb*)Pop("Bomb");

    bomb->Plant(pos);
}

void BombManager::SetLand(Texture* texture)
{
    vector<GameObject*> bombs = totalObjects["Bomb"];

    for (GameObject* bomb : bombs)
    {
        ((Bomb*)bomb)->SetLandTexture(texture);
    }
}

void BombManager::Clear()
{
    vector<GameObject*> bombs = totalObjects["Bomb"];

    for (GameObject* bomb : bombs)
    {
        bomb->isActive = false;
    }
}

void BombManager::CreateObjects(string key, UINT poolSize)
{
    vector<GameObject*> bombs(poolSize);

    for (GameObject*& bomb : bombs)
    {
        bomb = new Bomb();
        ((Bomb*)bomb)->SetBrush(hBrush, hPen);
    }

    totalObjects[key] = bombs;
}
