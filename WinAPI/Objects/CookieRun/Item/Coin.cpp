#include "Framework.h"

Coin::Coin(wstring file, UINT frameX, UINT frameY, COLORREF transColor)
    :Item(file, frameX, frameY, transColor)
{
    Audio::Get()->Add("GetCoin", "Sounds/Cookierun/GetCoin.wav");

    tag += "_Jelly";
}

Coin::~Coin()
{
}

void Coin::Update()
{
    Item::Update();

    CalculateValue();
}

void Coin::SetValue(float val)
{
    value = val;
    initValue = val;
}

void Coin::ActivateEffect(GameObject* object)
{
    Audio::Get()->Play("GetCoin", 0.5f);
    ScoreManager::Get()->coin += (UINT)value;
    isActive = false;
    DeactivateMoveTo();
}

void Coin::CalculateValue()
{
    value = initValue + pos.x * 0.001f;   
}
