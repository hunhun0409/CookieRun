#pragma once
class Item : public ImageRect
{
public:
	Item(wstring file, UINT frameX=1, UINT frameY = 1, COLORREF transparentColor = MAGENTA);
	~Item();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void CamRender(HDC hdc);

	virtual void ActivateEffect(GameObject* object) = 0;
	void DeactivateMoveTo();


	void SetTarget(GameObject* object);

private:
	void MoveTo();

public:
	bool isMove = false;
	Vector2 changePos;
	Vector2 initPos;

protected:
	Animation* animation;
	float moveSpeed = 15.0f;
	GameObject* target;
};