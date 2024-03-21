#include "Framework.h"


Item::Item(wstring file, UINT frameX, UINT frameY, COLORREF transparentColor)
	:ImageRect(file, frameX, frameY, transparentColor)
{
	animation = new Animation(texture->GetFrame());
	animation->SetDefault(true);
	animation->Play();
	tag = "Item";

	Audio::Get()->Add("GetPowerUp", "Sounds/Cookierun/GetPowerupitem.wav");
}

Item::~Item()
{
	delete animation;
}

void Item::Update()
{
	if (!isActive)
	{
		return;
	}

	ImageRect::Update();
	animation->Update();

	if (isMove)
		MoveTo();
}

void Item::Render(HDC hdc)
{
	ImageRect::Render(hdc, animation->GetFrame());
}

void Item::CamRender(HDC hdc)
{
	ImageRect::CamRender(hdc, animation->GetFrame());

}

void Item::DeactivateMoveTo()
{
	if (target)
	{
		target = nullptr;
		isMove = false;
	}
}


void Item::SetTarget(GameObject* object)
{
	if (target != nullptr) return;
	target = object;
	if (target)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}
}

void Item::MoveTo()
{
	Vector2 destPos;
	destPos = target->pos;
	destPos.x += 50;
	
	pos = Lerp(pos, destPos, moveSpeed * DELTA);
}
