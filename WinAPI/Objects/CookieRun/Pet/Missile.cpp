#include "Framework.h"

Missile::Missile()
{
	texture = Texture::Add(L"Textures/CookieRun/Pets/Missile.bmp", 2, 1);

	imageRect = new ImageRect(texture);
	size = { 300, 300 };

	animation = new Animation(texture->GetFrame());
	animation->SetDefault(true);
	animation->Play();

	tag = "Missile";

	speed = Speed;

	isActive = false;


	Texture* exp = Texture::Add(L"Textures/CookieRun/Pets/expEffect.bmp", 7, 1);
	EffectManager::Get()->Add("Missile_Exp", 20, exp);
}

Missile::~Missile()
{
	delete imageRect;
	delete animation;
}

void Missile::Update()
{
	if(!isActive) return;

	localPos.x += speed * DELTA;
	localPos.y += speed * DELTA;

	pos.x = localPos.x + Camera::Get()->GetPos().x + offset;
	pos.y = localPos.y + Camera::Get()->GetPos().y;

	imageRect->pos = pos;
	animation->Update();
	
	

	Explode();
}

void Missile::Render(HDC hdc)
{
	if(!isActive) return;

	if (KEY_DOWN(VK_TAB))
	{
		DebugMode = !DebugMode;
	}
	if(DebugMode)
		Rect::LineRender(hdc);

	imageRect->Render(hdc, animation->GetFrame());

}

void Missile::CamRender(HDC hdc)
{
	if (!isActive) return;
	if (KEY_DOWN(VK_TAB))
	{
		DebugMode = !DebugMode;
	}
	if (DebugMode)
		Rect::LineRender(hdc);

	imageRect->CamRender(hdc, animation->GetFrame());

}

void Missile::Spawn(Vector2 pos)
{
	isActive = true;
	localPos = {};
	this->pos = pos;
	offset = Random(100, 400);
}

void Missile::Explode()
{
	if (pos.y + 100  >= StageManager::Get()->GetGroundHeight(pos))
	{
		Audio::Get()->Play("Explosion", 0.5f);
		EffectManager::Get()->Play("Missile_Exp", pos);
		isActive = false;
		Observer::Get()->ExcuteParamEvents("Obstacle_Destroy", this);
	}
}
