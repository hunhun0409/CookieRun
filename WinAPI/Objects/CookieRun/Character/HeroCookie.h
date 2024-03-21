#pragma once
class HeroCookie : public CookieCharacter
{
public:
	HeroCookie();
	~HeroCookie();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Render(HDC hdc, int alpha = 255) override;

	virtual void Run() override;

	void SkillStart();
	void SkillLoop();
	void SkillEnd();

	virtual void Jump() override;
	virtual void JumpLoop() override;

	virtual void Slide() override;

private:
	virtual void CreateAnimation() override;

	virtual void SetAnimation() override;
private:
	ProgressBar* skillGauge;
};
