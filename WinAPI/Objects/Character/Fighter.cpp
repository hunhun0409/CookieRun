#include "Framework.h"

Fighter::Fighter()
    : BattleCharacter(L"Textures/Battle/Fighter.bmp", 3, 13)
{
    CreateAnimations();

    animations[curType]->Play();

    size = { 70, 120 };
    imageOffset = { 20, -5 };
}

Fighter::~Fighter()
{
}

void Fighter::Update()
{
    Control();    
    Attack();
    SetAnimation();

    CheckMoveTouchTime();

    BattleCharacter::Update();
}

void Fighter::Control()
{
    if (isAttack) return;

    bool isMove = false;

    if (KEY_DOWN(VK_RIGHT) || KEY_DOWN(VK_LEFT))
    {
        isMove = true;

        if (isMoveTouch)
        {
            isRun = true;            
        }
        else
        {
            isMoveTouch = true;
            touchTime = 0.0f;
        }        
    }

    if (KEY_PRESS(VK_RIGHT))
    {
        isMove = true;

        if (isRun)
            velocity.x = RUN_SPEED;
        else
            velocity.x = WALK_SPEED;
    }
    if (KEY_PRESS(VK_LEFT))
    {
        isMove = true;

        if (isRun)
            velocity.x = -RUN_SPEED;
        else
            velocity.x = -WALK_SPEED;
    }
    if (KEY_PRESS(VK_UP))
    {
        isMove = true;

        if (isRun)
            velocity.y = -RUN_SPEED;
        else
            velocity.y = -WALK_SPEED;
    }
    if (KEY_PRESS(VK_DOWN))
    {
        isMove = true;

        if (isRun)
            velocity.y = RUN_SPEED;
        else
            velocity.y = WALK_SPEED;
    }

    if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))        
    {
        velocity.x = 0.0f;        
    }

    if (KEY_UP(VK_UP) || KEY_UP(VK_DOWN))
    {
        velocity.y = 0.0f;        
    }

    if (!isMove)
    {
        velocity = {};
        isRun = false;
    }
}


void Fighter::Attack()
{
    if (isAttack) return;

    if (KEY_DOWN('Z'))
    {
        SetAction(PUNCH);
        isAttack = true;

        attackCollider->isActive = true;
        attackCollider->pos = pos + Vector2(50, 0);
        attackCollider->size = { 100, 70 };

        EffectManager::Get()->Play("Exp", attackCollider->pos);
    }

    if (KEY_DOWN('X'))
    {
        SetAction(KICK);
        isAttack = true;

        attackCollider->isActive = true;
        attackCollider->pos = pos + Vector2(20, 10);
        attackCollider->size = { 80, 40 };

        EffectManager::Get()->Play("Exp2", attackCollider->pos);
    }
}

void Fighter::SetAnimation()
{
    if (isAttack) return;

    if (velocity.Length() > 0.0f)
    {
        if (isRun)
            SetAction(RUN);
        else
            SetAction(WALK);
    }
    else
    {
        SetAction(IDLE);
    }
}

void Fighter::CreateAnimations()
{
    animations[IDLE] = new Animation(texture->GetFrame());
    animations[IDLE]->SetPart(23, 26, true);

    animations[WALK] = new Animation(texture->GetFrame());
    animations[WALK]->SetPart(27, 34, true);

    animations[RUN] = new Animation(texture->GetFrame());
    animations[RUN]->SetPart(7, 14, true);

    animations[PUNCH] = new Animation(texture->GetFrame());
    animations[PUNCH]->SetPart(0, 6);
    animations[PUNCH]->SetEndEvent(bind(&Fighter::EndAttack, this));

    animations[KICK] = new Animation(texture->GetFrame());
    animations[KICK]->SetPart(35, 38);
    animations[KICK]->SetEndEvent(bind(&Fighter::EndAttack, this));
}

void Fighter::CheckMoveTouchTime()
{
    if (!isMoveTouch)
        return;

    touchTime += DELTA;
    
    if (touchTime >= RUN_TOUCH_DELAY)
    {
        isMoveTouch = false;
        touchTime = 0.0f;
    }
}
