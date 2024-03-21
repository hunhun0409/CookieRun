#pragma once

class Giant : public Item
{
public:
	Giant();
	~Giant() = default;


	virtual void ActivateEffect(GameObject* object) override;

};
