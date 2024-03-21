#pragma once

class Ground : public ImageRect
{
public:
	Ground(wstring file, UINT frameX = 1, UINT frameY = 1,
		COLORREF transColor = MAGENTA);
	Ground(Texture* texture);
	~Ground() = default;

public:
	Vector2 changePos;
	Vector2 initPos;
};
