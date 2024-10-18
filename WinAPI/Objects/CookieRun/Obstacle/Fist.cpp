#include "Framework.h"

Fist::Fist()
	:Obstacle(L"Textures/CookieRun/Obstacles/PopUp_fist.bmp", 8, 1, true)
{
    size = { 80, 85 };
    imageOffset = { 20, -12 };
    CreateAnimation();
    animations[curState]->Play();
    
    tag += "_Fist";
}

Fist::~Fist()
{
}

void Fist::Update()
{
    if (!isActive) return;
    Obstacle::Update();
    
}

void Fist::Render(HDC hdc)
{
    if (!isSpawn) return;
    Obstacle::Render(hdc);
}

void Fist::CamRender(HDC hdc)
{
    if (!isSpawn) return;
    Obstacle::CamRender(hdc);
}

void Fist::Spawn()
{
    if (isSpawn) return;
    isSpawn = true;
    isActive = true;
    SetState(NOTICE);
}


void Fist::Uping()
{
    SetState(UPING);
}

void Fist::UpEnd()
{
    SetState(UPEND);
}

void Fist::Destroy(void* obj)
{
    if (!isSpawn) return;
    Obstacle::Destroy(obj);
}

void Fist::Init()
{
    Obstacle::Init();
    isSpawn = false;
}

void Fist::CreateAnimation()
{
    animations[NOTICE] = new Animation(texture->GetFrame(), 1.0f);
    animations[NOTICE]->SetPart(0, 1);
    animations[NOTICE]->SetEndEvent(bind(&Fist::Uping, this));

    animations[UPING] = new Animation(texture->GetFrame(), 1.0f);
    animations[UPING]->SetPart(2, 6);
    animations[UPING]->SetEndEvent(bind(&Fist::UpEnd, this));

    animations[UPEND] = new Animation(texture->GetFrame(), 1.0f);
    animations[UPEND]->SetPart(7, 7);
}
