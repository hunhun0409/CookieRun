#include "Framework.h"

Megaman::Megaman()
    : PixelCharacter(L"Textures/CookieRun/CookieRun.bmp", 11, 6)
{
    CreateAnimations();
    animations[curType]->Play();    
}

Megaman::~Megaman()
{    
}

void Megaman::Update()
{
    Control();
    Plant();      
    Move();

    PixelCharacter::Update();

    SetAnimation();
}

void Megaman::Move()
{
    if (curType == PLANT) return;

    if (CanMove())
        pos.x += velocity.x * DELTA;
}

void Megaman::Plant()
{
    if (curType == PLANT) return;

    if (KEY_DOWN(VK_SPACE))
    {
        SetAction(PLANT);

        Vector2 plantPos = pos;
        plantPos.y = Bottom();

        BombManager::Get()->Plant(plantPos);
    }
}

void Megaman::Control()
{
    if (curType == PLANT) return;

    bool isMove = false;

    if (KEY_PRESS(VK_RIGHT))
    {
        velocity.x = speed;
        isMove = true;
    }

    if (KEY_PRESS(VK_LEFT))
    {
        velocity.x = -speed;
        isMove = true;
    }

    if (!isMove)
        velocity.x = 0.0f;

    if (jumpCount < 2 && KEY_DOWN(VK_UP))
    {
        velocity.y = JUMP_POWER;
        jumpCount++;

        if (jumpCount >= 2)
        {
            SetAction(JUMP_DOWN);
        }
    }
}

void Megaman::SetAnimation()
{
    if (curType == PLANT) return;

    if (velocity.y > 10.0f)
    {
        SetAction(JUMP_UP);
        return;
    }
    else if(velocity.y < -50.0f)
    {
        SetAction(JUMP_DOWN);
        return;
    }

    if (abs(velocity.x) > 0)
        SetAction(RUN);
    else
        SetAction(IDLE);
}

void Megaman::SetIdle()
{
    SetAction(IDLE);
}

void Megaman::CreateAnimations()
{
    animations[IDLE] = new Animation(texture->GetFrame());
    animations[IDLE]->SetPart(22, 31, true);

    animations[RUN] = new Animation(texture->GetFrame());
    animations[RUN]->SetPart(11, 18, true);

    animations[JUMP_UP] = new Animation(texture->GetFrame());
    animations[JUMP_UP]->SetPart(33, 37);

    animations[JUMP_DOWN] = new Animation(texture->GetFrame());
    animations[JUMP_DOWN]->SetPart(0, 5);

    animations[PLANT] = new Animation(texture->GetFrame());
    animations[PLANT]->SetPart(53, 54);
    animations[PLANT]->SetEndEvent(bind(&Megaman::SetIdle, this));
}