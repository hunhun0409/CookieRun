#pragma once
class CookieCharacter : public Rect
{
protected:
	const float RUN_SPEED = 500.0f;
	const float DASH_SPEED = 1500.0f;
	
	const float JUMP_POWER = 800.0f;
	const float GRAVITY = 2400.0f;
	const UINT MAX_JUMP_NUM = 2;
	const float BOTTOM_CHECK = 10.0f;


	const float GHOST_TIME = 2.0f;
	const float ALPHA_SPEED = 1000.0f;

	const float GIANT_TIME = 3.0f;
	const float DASH_TIME = 2.0f;

	const float SKILL_COOLDOWN = 20;
	const float SKILL_DURATION = 4;

	const float BONUSTIME_DURATION = 5;

	enum CharacterState
	{
		RUN, DASH, SLIDE, SLIDE2RUN, 
		SKILL_START, SKILL_LOOP, SKILL_END,
		JUMP1, JUMP2_START, JUMP2_LOOP, JUMP2_END,
		BONUSTIME_START, BONUSTIME_LOOP, BONUSTIME_LOOP_UP, BONUSTIME_END,
		CRASH, EXHAUST, DEAD
	};

public:
	CookieCharacter(wstring file, int frameX, int frameY, COLORREF transColor = MAGENTA);
	CookieCharacter(Texture* texture);
	~CookieCharacter();

	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render(HDC hdc, int alpha);
protected:
	void MoveTo();

	virtual void Gravity();
	virtual void Control();
	virtual void Move();
	virtual void Run();

	virtual void Slide();

	virtual void Jump();
	virtual void JumpLoop();
	virtual void Land();

	virtual void Crash();
	virtual void EndCrash();
	virtual void Exhaust();
	virtual void Dead();

	void GiantStart();
	void GiantLoop();
	void GiantEnd();

	void DashStart();
	void DashLoop();
	void DashEnd();

	void BonustimeStart();
	void BonustimeLoop();
	void BonustimeEnd();

protected:
	float GetHeight(const Vector2& pos);
	
	virtual void CreateAnimation() = 0;
	virtual void SetAnimation() = 0;
	void SetAction(CharacterState state);
	void SetMoveTo(float dest);

public:
	bool IsInvincible() const { return isInvincible; }
	bool IsDead() { return curState == EXHAUST || curState == DEAD; }
	void SetHealth(float changeAmount);

public:
	bool isFly = false;
private:
	bool DebugMode = true;
protected:
	Texture* texture;

	ImageRect* imageRect;
	Vector2 imageOffset;

	map<CharacterState, Animation*> animations;

	CharacterState curState = RUN;

	Vector2 standSize;
	Vector2 crouchSize;

	Vector2 velocity = {};
	float maxSpeed = RUN_SPEED;

	UINT jumpCount = 0;

	bool isGhost = false;
	float ghostTime = 0.0f;

	bool isInvincible = false;

	bool isGiant = false;
	bool isShrink = false;
	float giantTime = GIANT_TIME;
	float pSize = 0.0f;

	bool isDash = false;
	float dashTime = DASH_TIME;

	bool isSkill = false;
	float cooldown = SKILL_COOLDOWN - 10.0;
	float duration = SKILL_DURATION;

	float flySpeed = 500;

	Vector2 normalSize;
	Vector2 giantSize;
	Vector2 crouchNormalSize;
	Vector2 crouchGiantSize;

	Vector2 imageNormalSize;
	Vector2 imageGiantSize;
	
	ProgressBar* hpBar;

	float moveToSpeed = 4;
	bool isMoveTo = false;
	float destHeight;
	
	float maxHP = 100;
	float curHP = 100;
};
