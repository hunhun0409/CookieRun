#include "Framework.h"

Pet::Pet(wstring file1, UINT frameX1, UINT frameY1, COLORREF transColor1, wstring file2, UINT frameX2, UINT frameY2, COLORREF transColor2)
{
	textures[TRACE] = Texture::Add(file1, frameX1, frameY1, transColor1);
	imageRects[TRACE] = new ImageRect(textures[TRACE]);

	textures[SKILL] = Texture::Add(file2, frameX2, frameY2, transColor2);
	imageRects[SKILL] = new ImageRect(textures[SKILL]);

	size = { 80, 80 };
	tag = "Pet";

	CreateAnimation();
	animations[curState]->Play();
	

	magnetRect = new Rect(pos, { CENTER_X, WIN_HEIGHT });
	magnetRect->isActive = false;
	magnetRect->tag = "magnetRect";

	Observer::Get()->AddEvent("ActivateMagnet", bind(&Pet::MagnetOn, this));


	MissileManager::Get()->SetOwner(this);
	
}

Pet::~Pet()
{
	for (pair<State, ImageRect*> imageRect : imageRects)
	{
		delete imageRect.second;
	}
	delete magnetRect;
}

void Pet::Update()
{
	if (isFollow)
		Follow();
	else
		Center();
	magnetRect->pos = pos;

	imageRects[curState]->pos = pos + imageOffsets[curState];
	if(animations.count(curState) > 0)
		animations[curState]->Update();
	

	MissileManager::Get()->Update();

	if (owner->IsDead())return;
	if(!BonusTimeManager::Get()->isBonusTime)
		skillCooltime -= DELTA;
	Skill();
	
}

void Pet::Render(HDC hdc)
{
	if (KEY_DOWN(VK_TAB))
	{
		DebugMode = !DebugMode;
	}
	if (DebugMode)
	{
		Rect::LineRender(hdc);
		magnetRect->LineRender(hdc);

	}
	

	imageRects[curState]->Render(hdc, animations[curState]->GetFrame());


	//MissileManager::Get()->Render(hdc);

}

void Pet::CamRender(HDC hdc)
{
	if (KEY_DOWN(VK_TAB))
	{
		DebugMode = !DebugMode;
	}
	if (DebugMode)
	{
		Rect::CamLineRender(hdc);
		magnetRect->LineRender(hdc);

	}

	imageRects[curState]->CamRender(hdc, animations[curState]->GetFrame());


	MissileManager::Get()->Render(hdc);
}

void Pet::SetState(State state)
{
	if (curState == state) return;
	curState = state;
	animations[state]->Play();
}

void Pet::SetOwner(CookieCharacter* target)
{
	owner = target;
}

void Pet::Trace()
{
	SetState(TRACE);
}

void Pet::Follow()
{
	if (owner == nullptr) return;

	
	destPos = owner->pos + followOffset;
	pos.x = Lerp(pos.x, destPos.x, followSpeed * DELTA);
	pos.y = Lerp(pos.y, destPos.y, 2*followSpeed * DELTA);
}

void Pet::Center()
{
	if (owner == nullptr) return;

	timeElapsed += DELTA;

	if (timeElapsed >= MagnetTime)
	{
		timeElapsed = 0.0f;
		MagnetOff();
	}

	destPos = Camera::Get()->GetPos() + Vector2(CENTER_X, CENTER_Y);

	pos = Lerp(pos, destPos, centerSpeed * DELTA);
}

void Pet::MagnetOn()
{
	isFollow = false;
	
	magnetRect->isActive = true;
}

void Pet::MagnetOff()
{
	isFollow = true;
	magnetRect->isActive = false;

	Observer::Get()->ExcuteEvents("DeactivateMagnet");
}

void Pet::Skill()
{
	if (curState == SKILL) return;
	if (skillCooltime <= 0)
	{
		SetState(SKILL);
	}
}

void Pet::SkillEnd()
{
	skillCooltime = SkillCooldown;
	SetState(TRACE);
}

void Pet::CreateAnimation()
{
	animations[TRACE] = new Animation(textures[TRACE]->GetFrame());
	animations[TRACE]->SetDefault(true);

	animations[SKILL] = new Animation(textures[SKILL]->GetFrame());
	animations[SKILL]->SetDefault();
	animations[SKILL]->SetNotifyEvent(bind(&Pet::OnNotifyBegin, this, placeholders::_1), 17, "SpawnMissile");
	animations[SKILL]->SetEndEvent(bind(&Pet::SkillEnd, this));
	
	


	//animations[RUN] = new Animation(texture->GetFrame(), 1.2f);
	//animations[RUN]->SetPart(13, 16, true);

	//animations[JUMP1] = new Animation(texture->GetFrame(), 1.2f);
	//animations[JUMP1]->SetPart(7, 8, true);

	//animations[JUMP2_START] = new Animation(texture->GetFrame(), 1.2f);
	////animations[JUMP2_START]->SetPart(0, 4);
	//int arr[] = { 0, 1, 2, 3, 1, 2, 3, 4 };
	//animations[JUMP2_START]->SetArray(arr, 8);
	//animations[JUMP2_START]->SetEndEvent(bind(&HeroCookie::JumpLoop, this));
}


void Pet::OnNotifyBegin(string name)
{
	if (name == "SpawnMissile")
	{
		MissileManager::Get()->IsSpawn() = true;
	}
}
