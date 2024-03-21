#include "Framework.h"

Energy::Energy()
	:Item(L"Textures/CookieRun/Items/Energy.bmp", 1, 1)
{
	Audio::Get()->Add("GetEnergy", "Sounds/Cookierun/GetEnergy.wav");

	tag += "_PowerUp";
}



void Energy::ActivateEffect(GameObject* object)
{
	isActive = false;
	Audio::Get()->Play("GetEnergy", 0.5f);
	DeactivateMoveTo();


	if (object->tag == "Pet")
	{
		CookieCharacter* cookie = ((Pet*)object)->GetOwner();

		if (cookie)
		{
			cookie->SetHealth(10);
		}
	}
	else
	{
		CookieCharacter* cookie = (CookieCharacter*)object;
		cookie->SetHealth(10);
	}
	
}
