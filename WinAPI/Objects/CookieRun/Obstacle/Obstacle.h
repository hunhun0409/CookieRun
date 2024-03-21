#pragma once
class Obstacle : public Rect
{
public:
	Obstacle(wstring file, UINT frameX = 1, UINT frameY = 1, bool adjust = false, COLORREF transColor = MAGENTA);
	~Obstacle();

	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void CamRender(HDC hdc);

	virtual void Destroy(void* obj);

	virtual void Init();

	void ResetPos();
	void Gravity();



protected:
	void SetState(int state);
	virtual void CreateAnimation(){};

public:
	Vector2 changePos;
	Vector2 initPos;
private:
	bool isDebug = true;
protected:
	Texture* texture;

	ImageRect* imageRect;
	Vector2 imageOffset;
	map<int, Animation*> animations;

	int curState = 0;

	bool isAdjust;

};
