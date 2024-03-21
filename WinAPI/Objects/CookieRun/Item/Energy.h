#pragma once
class Energy : public Item
{
public:
	Energy();
	~Energy() = default;


	virtual void ActivateEffect(GameObject* object) override;
private:
	float recoverAmount = 10;
};