#pragma once

class Magnet : public Item
{
public:
	Magnet();
	~Magnet() = default;


	virtual void ActivateEffect(GameObject* object) override;
private:

};
