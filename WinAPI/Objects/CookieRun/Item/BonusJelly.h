#pragma once

class BonusJelly : public Item
{
public:
	BonusJelly(UINT idx);
	~BonusJelly() = default;

	virtual void CamRender(HDC hdc) override;

	virtual void ActivateEffect(GameObject* object) override;

private:
	int idx;
	POINT p;
};
