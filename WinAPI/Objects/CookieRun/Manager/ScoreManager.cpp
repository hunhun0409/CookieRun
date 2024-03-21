#include "Framework.h"

ScoreManager::ScoreManager()
{
	jellyIcon = new ImageRect(L"Textures/Cookierun/UI/ingameJelly.bmp");

	scoreDigits.resize(10);

	for (Digit*& digit : scoreDigits)
	{
		digit = new Digit();
		digit->pos.y = 100;
	}


	coinIcon = new ImageRect(L"Textures/Cookierun/UI/ingameCoin.bmp");

	coinDigits.resize(10);

	for (Digit*& digit : coinDigits)
	{
		digit = new Digit();
		digit->pos.y = 100;
	}
}

ScoreManager::~ScoreManager()
{
	for (Digit* digit : scoreDigits)
	{
		delete digit;
	}
	for (Digit* digit : coinDigits)
	{
		delete digit;
	}
}

void ScoreManager::Update()
{
	SplitScore();
	for (int i = 0; i < scoreDigitCount; i++)
	{
		/*float j = (float)digitCount / 2.0f;
		digits[i]->pos.x = (CENTER_X - 25 * i) + offset*(2*digitCount-1) ;*/

		float j = (float)scoreDigitCount / 2.0f;
		scoreDigits[i]->pos.x = (CENTER_X - 25 * i) + offset * (scoreDigitCount - 1);
	}
	jellyIcon->pos = scoreDigits[scoreDigitCount - 1]->pos;
	jellyIcon->pos.x -= 32;

	SplitCoin();
	for (int i = 0; i < coinDigitCount; i++)
	{
		float j = (float)coinDigitCount / 2.0f;
		coinDigits[i]->pos.x = (50 - 25 * i) + offset*(2*coinDigitCount-1);
	}
	coinIcon->pos = coinDigits[coinDigitCount - 1]->pos;
	coinIcon->pos.x -= 32;
}

void ScoreManager::Render(HDC hdc)
{
	for (int i = 0; i < scoreDigitCount; i++)
	{
		scoreDigits[i]->Render(hdc);
	}
	jellyIcon->Render(hdc);
	for (int i = 0; i < coinDigitCount; i++)
	{
		coinDigits[i]->Render(hdc);
	}
	coinIcon->Render(hdc);
}

void ScoreManager::SplitScore()
{
	scoreDigitCount = countScoreDigits();
	UINT temp = score;
	for (int i = 0; i < scoreDigitCount; ++i) 
	{
		UINT a = temp % 10; // 맨 뒷자리수
		temp /= 10;
		scoreDigits[i]->SetDigit(a); 
	}
}

void ScoreManager::SplitCoin()
{
	coinDigitCount = countCoinDigits();
	UINT temp = coin;
	for (int i = 0; i < coinDigitCount; ++i)
	{
		UINT a = temp % 10; // 맨 뒷자리수
		temp /= 10;
		coinDigits[i]->SetDigit(a);
	}
}
void ScoreManager::SetScore()
{
	string key = StageManager::Get()->Key();
	if (highScoreData.count(key) > 0)
	{
		if (highScoreData[key] < score)
		{
			highScoreData[key] = score;
			//신기록 갱신 알림
		}
	}
	else
	{
		highScoreData[key] = score;
		//신기록 갱신 알림
	}
}

UINT ScoreManager::countScoreDigits() {
	if (score == 0) return 1; // 0은 1자리수
	UINT temp = score;
	int count = 0;
	while (temp != 0) {
		temp /= 10; // 한 자리수씩 줄임
		++count; // 자릿수 증가
	}
	return count;
}

UINT ScoreManager::countCoinDigits()
{
	if (coin == 0) return 1; // 0은 1자리수
	UINT temp = coin;
	int count = 0;
	while (temp != 0) {
		temp /= 10; // 한 자리수씩 줄임
		++count; // 자릿수 증가
	}
	return count;
}
