#include "Framework.h"

Siva::Siva()
    : PixelCharacter(L"Textures/siva_run.bmp", 8, 2)
{
    CreateAnimations();

    animations[IDLE_LEFT]->Play();      

    Observer::Get()->AddParamEvent("SivaDamage", bind(&Siva::Damage, this, placeholders::_1));
}

Siva::~Siva()
{
}

void Siva::Update()
{
    ActionState();

    PixelCharacter::Update();
}

void Siva::Render(HDC hdc)
{
    ImageRect::CamRender(hdc, (int)alphaValue, animations[curType]->GetFrame());
}

void Siva::Damage(void* bomb)
{
    GameObject* object = (GameObject*)bomb;

    float distance = (pos - object->pos).Length();

    if (distance < 100)
    {
        state = HIT;

        if (velocity.x > 0)
            SetAction(IDLE_RIGHT);
        else
            SetAction(IDLE_LEFT);
    }
}

void Siva::ActionState()
{
    switch (state)
    {
    case Siva::PATROL:
        Patrol();
        break;
    case Siva::IDLE:
        Idle();
        break;
    case Siva::HIT:
        Hit();
        break;
    default:
        break;
    }
}

void Siva::Patrol()
{
    patrolTime += DELTA;

    if (CanMove())
    {        
        pos.x += velocity.x * DELTA;
    }    
    else
    {
        velocity.x *= -1.0f;
    }    

    if (velocity.x > 0)
        SetAction(RUN_RIGHT);
    else
        SetAction(RUN_LEFT);

    if (patrolTime >= PATROL_TIME)
    {
        state = IDLE;
        if (velocity.x > 0)
            SetAction(IDLE_RIGHT);
        else
            SetAction(IDLE_LEFT);

        patrolTime = 0.0f;
    }

    if (Left() < 0.0f)
    {
        velocity.x = SPEED;
    }
    else if (Right() > landTexture->GetSize().x)
    {
        velocity.x = -SPEED;
    }
}

void Siva::Hit()
{
    hitTime += DELTA;

    if (isIncreaseAlpha)
    {
        alphaValue += BLINK_SPEED * DELTA;

        if (alphaValue > 255.0f)
            isIncreaseAlpha = false;
    }
    else
    {
        alphaValue -= BLINK_SPEED * DELTA;

        if (alphaValue < 0.0f)
            isIncreaseAlpha = true;
    }

    if (hitTime >= HIT_TIME)
    {
        alphaValue = 255.0f;
        hitTime = 0.0f;
        state = IDLE;
    }

}

void Siva::Idle()
{
    idleTime += DELTA;

    if (idleTime >= IDLE_TIME)
    {
        idleTime = 0.0f;
        StartPatrol();
    }
}

void Siva::StartPatrol()
{
    state = PATROL;

    velocity.x = (rand() % 2) ? -SPEED : SPEED;

    velocity.y = JUMP_POWER;
}

void Siva::CreateAnimations()
{
    animations[IDLE_LEFT] = new Animation(texture->GetFrame(), 0.2f);
    animations[IDLE_LEFT]->SetPart(14, 15, true, true);

    animations[IDLE_RIGHT] = new Animation(texture->GetFrame(), 0.2f);
    animations[IDLE_RIGHT]->SetPart(0, 1, true, true);

    animations[RUN_LEFT] = new Animation(texture->GetFrame());
    animations[RUN_LEFT]->SetPart(8, 13, true);

    animations[RUN_RIGHT] = new Animation(texture->GetFrame());
    animations[RUN_RIGHT]->SetPart(2, 7, true);
}
