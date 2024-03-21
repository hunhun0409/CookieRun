#pragma once
class Pet : public Rect
{
private:
	const float MagnetTime = 5.0f;
	const float SkillCooldown = 15.0f;

protected:
	enum State {
		TRACE, SKILL 
	};
public:
	Pet(wstring file1, UINT frameX1, UINT frameY1, COLORREF transColor1,
		wstring file2, UINT frameX2, UINT frameY2, COLORREF transColor2 = MAGENTA);
	~Pet();

	void Update();
	void Render(HDC hdc);
	void CamRender(HDC hdc);

	void SetState(State state);
	void SetOwner(CookieCharacter* target);
	CookieCharacter* GetOwner() { return owner; }

	void Trace();

	void Follow();
	void Center();

	void MagnetOn();
	void MagnetOff();

	void Skill();
	void Spawn();
	void SkillEnd();

	Rect* GetMagnetRect() { return magnetRect; }

	void CreateAnimation();

	void OnNotifyBegin(string name);

private:
	bool DebugMode = true;
public:
	bool isFollow = true;

private:
	map<State, Texture*> textures;

	map<State, ImageRect*> imageRects;
	map<State, Vector2> imageOffsets;
	State curState = TRACE;

	map<State, Animation*> animations;

	CookieCharacter* owner = nullptr;

	Vector2 destPos;
	Vector2 followOffset = { -60, -80};
	float followSpeed = 15.0f;
	float centerSpeed = 15.0f;

	Vector2 centerOffset = { 200, -200 };

	float timeElapsed = 0.0f;

	Rect* magnetRect;
	float skillCooltime = 3.0f;

};
