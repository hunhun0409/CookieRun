#include "Framework.h"

BonusJelly::BonusJelly(UINT idx)
	:Item(L"Textures/CookieRun/Items/BonusTimeFront.bmp", 9, 1)
{
	this->idx = idx;
	p = { this->idx, 0 };
	tag += "_Jelly";
	animation->Stop();
}


void BonusJelly::CamRender(HDC hdc)
{
	ImageRect::CamRender(hdc, p);

}

void BonusJelly::ActivateEffect(GameObject* object)
{
	isActive = false;
	DeactivateMoveTo();
	Audio::Get()->Play("GetJelly", 0.5f);
	BonusTimeManager::Get()->GetBonusJelly(idx);
}
