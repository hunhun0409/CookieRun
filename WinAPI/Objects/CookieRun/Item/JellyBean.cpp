#include "Framework.h"

JellyBean::JellyBean(wstring file, UINT frameX, UINT frameY, COLORREF transColor)
    : Item(file, frameX, frameY, transColor)
{
    Audio::Get()->Add("GetJelly", "Sounds/Cookierun/GetJelly.wav");

    tag += "_Jelly";

}

void JellyBean::Update()
{
    Item::Update();

    CalculateValue();
}

void JellyBean::ActivateEffect(GameObject* object)
{
    Audio::Get()->Play("GetJelly", 0.5f);
    ScoreManager::Get()->score += (UINT)value;
    isActive = false;
    DeactivateMoveTo();
}

void JellyBean::SetValue(float val)
{
    value = val;
    initValue = value;
}

void JellyBean::CalculateValue()
{
    value = initValue + pos.x * 0.001f;
}
