#pragma once

class JellyBean : public Item
{
public:
	JellyBean(wstring file, UINT frameX= 1, UINT frameY = 1, COLORREF transColor = MAGENTA);

    virtual void Update() override;

    void SetValue(float val);

private:
    virtual void ActivateEffect(GameObject* object) override;
    void CalculateValue();
private:
    float initValue;
    float value = 10;
};