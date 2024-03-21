#pragma once

class LobbyScene : public Scene
{
private:
	const float BLINK_INTERVAL = 3.0f;
	const float BLINK_DURATION = 0.2f;
public:
	LobbyScene();
	~LobbyScene();

private:

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

	void CookieAnimation();

	void StartCookieRunScene();

private:
	ImageRect* bg;
	Button* startButton;

	HFONT hFont;

	ImageRect* cookieThumbnail;
	POINT point = { 0,0 };
	bool isBlink = false;
	float blinkInterval = BLINK_INTERVAL;
	float blinkDuration = BLINK_DURATION;
	CookieCharacter* cookie;
};
