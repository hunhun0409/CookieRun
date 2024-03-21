#pragma once

class Coin : public Item
{
public:
    Coin(wstring file, UINT frameX = 1, UINT frameY = 1, COLORREF transColor = MAGENTA);
    ~Coin();

    virtual void Update() override;
    void SetValue(float val);
private:
    virtual void ActivateEffect(GameObject* object) override;

    void CalculateValue();
private:
    float initValue;
    float value;
};