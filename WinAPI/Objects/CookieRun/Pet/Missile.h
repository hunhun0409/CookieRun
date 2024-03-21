#pragma once

class Missile : public Rect
{
private:
	const float Speed = 600.0f;
public:
	Missile();
	~Missile();

	void Update();
	void Render(HDC hdc);
	void CamRender(HDC hdc);
	
	void Spawn(Vector2 pos);
	void Explode();

private:
	bool DebugMode = true;
private:
	Vector2 localPos = {};
	float offset;

	Texture* texture;

	ImageRect* imageRect;
	Animation* animation;

	float speed;
};
