#include "Framework.h"

Giant::Giant()
	:Item(L"Textures/cookierun/items/giant.bmp", 1, 1)
{
	tag += "_PowerUp";
}

void Giant::ActivateEffect(GameObject* object)
{
	isActive = false;
	DeactivateMoveTo();
	Audio::Get()->Play("GetPowerUp", 0.5f);
	Observer::Get()->ExcuteEvents("CookieGrow");
	
}
