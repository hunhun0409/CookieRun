#include "Framework.h"


Obstacle::Obstacle(wstring file, UINT frameX, UINT frameY, bool adjust, COLORREF transColor)
	:isAdjust(!adjust)
{
	texture = Texture::Add(file, frameX, frameY, transColor);

	imageRect = new ImageRect(texture);
	size = texture->GetSize();


	isActive = true;

	tag = "Obstacle";

	Observer::Get()->AddParamEvent("Obstacle_Destroy", bind(&Obstacle::Destroy, this, placeholders::_1));

	Texture* exp = Texture::Add(L"Textures/CookieRun/Effects/ChangeEffect.bmp", 4, 1);

	Audio::Get()->Add("CrashObstacle", "Sounds/CookieRun/crash_obstacle.wav");
	Audio::Get()->Add("Explosion", "Sounds/CookieRun/explosion.wav");

	EffectManager::Get()->Add("Obstacle_Destroy", 10, exp);
}

Obstacle::~Obstacle()
{
	delete imageRect;
}

void Obstacle::Update()
{
	if (!isActive) return;

	Gravity();

	imageRect->pos = pos + imageOffset;

	if (animations.count(curState) > 0)
		animations[curState]->Update();
}

void Obstacle::Render(HDC hdc)
{
	if (!isActive) return;

	if (isDebug)
		Rect::CamLineRender(hdc);

	if (KEY_DOWN(VK_TAB))
		isDebug = !isDebug;

	if (animations.count(curState) == 0)
	{
		imageRect->Render(hdc);
		return;
	}
	imageRect->Render(hdc, animations[curState]->GetFrame());
}

void Obstacle::CamRender(HDC hdc)
{
	if (!isActive) return;

	if(isDebug)
		Rect::CamLineRender(hdc);

	if (KEY_DOWN(VK_TAB))
		isDebug = !isDebug;

	if (animations.count(curState) == 0)
	{
		imageRect->CamRender(hdc);
		return;
	}

	imageRect->CamRender(hdc, animations[curState]->GetFrame());

	string a = to_string(animations[curState]->GetFrame().x);
	TextOutA(hdc, CENTER_X, CENTER_Y, a.c_str(), a.size());
}

void Obstacle::Destroy(void* obj)
{
	if (!isActive) return;
	Missile* missile = (Missile*)obj;
	if (missile != nullptr)
	{
		Vector2 v = missile->pos - pos;
		v.y = 0;
		if (v.Length() < 300)//미사일 터진위치에서 300범위 이내에 있으면
		{
			Audio::Get()->Play("Explosion", 0.5f);
			EffectManager::Get()->Play("Obstacle_Destroy", pos);
			isActive = false;
		}
	}
	else
	{
		Audio::Get()->Play("Explosion", 0.5f);
		EffectManager::Get()->Play("Obstacle_Destroy", pos);
		isActive = false;
	}
}

void Obstacle::Init()
{
	SetState(0);
	isActive = false;
}

void Obstacle::ResetPos()
{
	pos = initPos;
}

void Obstacle::Gravity()
{
	if (isAdjust) return;
	Vector2 bottomPos = pos;
	//bottomPos.y = Top();
	float groundHeight = StageManager::Get()->GetGroundHeight(bottomPos);

	if (Bottom() != groundHeight)
	{
		pos.y = groundHeight - Half().y;
		initPos.y = pos.y;
		changePos.y = pos.y;
		isAdjust = true;
	}
}

void Obstacle::SetState(int state)
{
	if (!isActive) return;
	if (curState == state) return;

	curState = state;
	animations[curState]->Play();
}
