#include "Framework.h"

BonusTimeManager::BonusTimeManager()
{
	bonusTimeBack = new ImageRect(L"Textures/CookieRun/UI/BonusTime.bmp");
	bonusTimeBack->pos = { 160, 50 };

	bonusTime.resize(9);
	bonusTime[0] = new ImageRect(L"Textures/CookieRun/UI/B.bmp");
	bonusTime[1] = new ImageRect(L"Textures/CookieRun/UI/O.bmp");
	bonusTime[2] = new ImageRect(L"Textures/CookieRun/UI/N.bmp");
	bonusTime[3] = new ImageRect(L"Textures/CookieRun/UI/U.bmp");
	bonusTime[4] = new ImageRect(L"Textures/CookieRun/UI/S.bmp");
	bonusTime[5] = new ImageRect(L"Textures/CookieRun/UI/T.bmp");
	bonusTime[6] = new ImageRect(L"Textures/CookieRun/UI/I.bmp");
	bonusTime[7] = new ImageRect(L"Textures/CookieRun/UI/M.bmp");
	bonusTime[8] = new ImageRect(L"Textures/CookieRun/UI/E.bmp");

	bonusTime[0]->pos = { 22, 50 };
	bonusTime[1]->pos = { 57, 50 };
	bonusTime[2]->pos = { 94, 50 };
	bonusTime[3]->pos = { 131, 50 };
	bonusTime[4]->pos = { 169, 50 };
	bonusTime[5]->pos = { 201, 50 };
	bonusTime[6]->pos = { 230, 50 };
	bonusTime[7]->pos = { 261, 50 };
	bonusTime[8]->pos = { 299, 50 };

	for (GameObject* b : bonusTime)
	{
		b->isActive = false;
	}

	Audio::Get()->Add("BonusTimeBGM", "Sounds/CookieRun/BonusTimeBGM.wav", true);
}

BonusTimeManager::~BonusTimeManager()
{
	delete bonusTimeBack;

	for (ImageRect* b : bonusTime)
	{
		delete b;
	}

}

void BonusTimeManager::Update()
{
	if (isBonusTime && startBonus)
	{
		StageManager::Get()->ChangeScene("BonusTime");
		Observer::Get()->ExcuteEvents("BonusTimeStart");
		startBonus = false;
	}

	if (isBonusTime)
	{
		bonusTimeDuration -= DELTA;

		if (bonusTimeDuration <= 0)
		{
			isBonusTime = false;
			bonusTimeDuration = BONUSTIME_DURATION;
			Observer::Get()->ExcuteEvents("BonusTimeEnd");
			string oldKey = StageManager::Get()->OldKey();
			StageManager::Get()->ChangeScene(oldKey);

			for (GameObject* b : bonusTime)
			{
				b->isActive = false;
			}

			Audio::Get()->Stop("BonusTimeBGM");
			Audio::Get()->Resume("HeroBGM");
		}
	}
}

void BonusTimeManager::Render(HDC hdc)
{
	bonusTimeBack->Render(hdc);
	for (ImageRect* b : bonusTime)
	{
		b->Render(hdc);
	}
}

void BonusTimeManager::Init()
{
}

void BonusTimeManager::GetBonusJelly(UINT idx)
{
	if (bonusTime[idx]->isActive) return;
	bonusTime[idx]->isActive = true;
	needCount--;
	if (needCount == 0)
	{
		isBonusTime = true;
		startBonus = true;
		needCount = 9;
		Audio::Get()->Pause("HeroBGM");
		Audio::Get()->Play("BonusTimeBGM");

	}
}
