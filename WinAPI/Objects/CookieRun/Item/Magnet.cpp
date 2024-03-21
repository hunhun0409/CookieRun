#include "Framework.h"

Magnet::Magnet()
	:Item(L"Textures/CookieRun/Items/Magnet.bmp", 1, 1)
{
	size = { 60, 60 };

	tag += "_PowerUp";
}

void Magnet::ActivateEffect(GameObject* object)
{
	isActive = false;
	DeactivateMoveTo();
	Audio::Get()->Play("GetPowerUp", 0.5f);
	Observer::Get()->ExcuteEvents("ActivateMagnet");
	
}
