#pragma once

class BonusTimeManager : public Singleton<BonusTimeManager>
{
private:
	const float BONUSTIME_DURATION = 8.0f;
private:
	friend class Singleton;
	BonusTimeManager();
	~BonusTimeManager();

public:
	void Update();
	void Render(HDC hdc);

	void Init();

	void GetBonusJelly(UINT idx);

public:
	bool startBonus = false;
	bool isBonusTime = false;
private:
	ImageRect* bonusTimeBack;
	vector<ImageRect*> bonusTime;
	float offset = 12.5f;

	float bonusTimeDuration = BONUSTIME_DURATION; 

	UINT needCount = 9;
};
