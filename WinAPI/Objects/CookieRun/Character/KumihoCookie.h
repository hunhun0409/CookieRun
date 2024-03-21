#pragma once
class KumihoCookie : public CookieCharacter
{
private:

public:
	KumihoCookie();
	~KumihoCookie();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Run() override;
	virtual void JumpLoop() override;
	
private:
	virtual void CreateAnimation() override;

	virtual void SetAnimation() override;


};