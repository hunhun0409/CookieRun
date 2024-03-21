#pragma once

class Invincible : public Item
{
public:
	Invincible();
	~Invincible() = default;


	virtual void ActivateEffect(GameObject* object) override;
};
