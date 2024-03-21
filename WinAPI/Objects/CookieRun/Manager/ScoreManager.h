#pragma once

class ScoreManager : public Singleton<ScoreManager>
{
private:
	friend class Singleton;
	ScoreManager();
	~ScoreManager();

public:
	void Update();
	void Render(HDC hdc);

	void SplitScore();
	void SplitCoin();

	void SetScore();

	UINT countScoreDigits();
	UINT countCoinDigits();

	UINT score = 0;//점수
	UINT coin = 0;

private:
	ImageRect* jellyIcon;

	vector<Digit*> scoreDigits;
	UINT scoreDigitCount;//자리수
	float offset = 12.5f;

	map<string, float> highScoreData;

	ImageRect* coinIcon;

	vector<Digit*> coinDigits;
	UINT coinDigitCount;

};
