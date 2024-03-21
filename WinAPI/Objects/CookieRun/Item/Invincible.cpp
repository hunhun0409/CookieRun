#include "Framework.h"

Invincible::Invincible()
	:Item(L"Textures/CookieRun/Items/Dash.bmp", 1, 1)
{
	tag += "_PowerUp";
}


void Invincible::ActivateEffect(GameObject* object)
{
	isActive = false;
	DeactivateMoveTo();

	Audio::Get()->Play("GetPowerUp", 0.5f);
	Observer::Get()->ExcuteEvents("CookieDash");
}
