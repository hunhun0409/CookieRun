#include "Framework.h"

Monster::Monster()
    : BattleCharacter(L"Textures/Battle/Monster.bmp", 6, 5)
{
    CreateAnimations();
    animations[curType]->Play();

    traceRange = new Circle(Vector2(), TRACE_RANGE);
    attackRange = new Rect(Vector2(), Vector2(100, 100));

    pos = { CENTER_X + 100, CENTER_Y };
    destPos = pos;

    size = texture->GetSize();

    Texture* frontTexture = Texture::Add(L"Textures/Pixel/hp_bar.bmp");
    Texture* backTexture = Texture::Add(L"Textures/Pixel/hp_bar_BG.bmp");

    hpBar = new ProgressBar(frontTexture, backTexture);
}

Monster::~Monster()
{
    delete traceRange;
    delete attackRange;
}

void Monster::Update()
{
    traceRange->pos = pos;
    attackRange->pos = pos;

    hpBar->pos = pos + Vector2(0, -50);
    hpBar->SetValue(curHp / maxHp);

    SetState();
    ActionState();
    SetAnimation();

    BattleCharacter::Update();
}

void Monster::Render(HDC hdc)
{
    HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    SelectObject(hdc, brush);

    traceRange->Render(hdc);
    attackRange->Render(hdc);

    BattleCharacter::Render(hdc);

    hpBar->Render(hdc);
}

void Monster::Damage()
{
    if (curType == HIT) return;
    if (curType == DEATH) return;

    SetAction(HIT);
    Audio::Get()->Play("Hit");

    curHp -= 10.0f;

    if (curHp <= 0.0f)
    {
        state = State::DEATH;
        SetAction(DEATH);
    }
}

void Monster::Move()
{
    if (curType == ATTACK) return;
    if (curType == HIT) return;
    if (curType == DEATH) return;

    pos += velocity * speed * DELTA;
}

void Monster::SetState()
{
    if (state == State::HIT) return;
    if (state == State::DEATH) return;

    if (attackRange->IsCollision(target))
    {
        state = State::ATTACK;
    }
    else if (traceRange->IsCollision(target))
    {
        state = State::TRACE;
    }
    else
    {
        state = State::PARTROL;
    }
    
}

void Monster::ActionState()
{
    switch (state)
    {
    case Monster::State::PARTROL:
        Patrol();
        break;
    case Monster::State::TRACE:
        Trace();
        break;
    case Monster::State::ATTACK:
        Attack();
        break;
    case Monster::State::HIT:
        Hit();
        break;
    case Monster::State::DEATH:
        Death();
        break;
    }
}

void Monster::SetAnimation()
{
    if (curType == ATTACK) return;
    if (curType == HIT) return;
    if (curType == DEATH) return;

    if (velocity.Length() > 0.0f)
        SetAction(RUN);
    else
        SetAction(IDLE);
}

void Monster::Patrol()
{
    velocity = {};
    SetAction(IDLE);
    //float distance = (pos - destPos).Length();

    //if (distance < 10.0f)
    //{
    //    destPos.x = Random(-PATROL_RANGE, PATROL_RANGE) + pos.x;
    //    destPos.y = Random(-PATROL_RANGE, PATROL_RANGE) + pos.y;
    //
    //    velocity = (destPos - pos).GetNormalized();
    //}
}

void Monster::Trace()
{
    velocity = (target->pos - pos).GetNormalized();
}

void Monster::Attack()
{
    if(curType == HIT) return;
    if (curType == DEATH) return;

    velocity = {};

    SetAction(ATTACK);
}

void Monster::EndAttack()
{
    SetAction(IDLE);
}

void Monster::Hit()
{
}

void Monster::Death()
{
}

void Monster::CreateAnimations()
{
    animations[IDLE] = new Animation(texture->GetFrame());
    animations[IDLE]->SetPart(0, 3, true);

    animations[RUN] = new Animation(texture->GetFrame());
    animations[RUN]->SetPart(6, 9, true);

    int arr[] = { 12, 12, 12, 12 };
    animations[HIT] = new Animation(texture->GetFrame());
    animations[HIT]->SetArray(arr, 4);
    animations[HIT]->SetEndEvent(bind(&Monster::EndAttack, this));

    animations[ATTACK] = new Animation(texture->GetFrame());
    animations[ATTACK]->SetPart(18, 21);
    animations[ATTACK]->SetEndEvent(bind(&Monster::EndAttack, this));

    animations[DEATH] = new Animation(texture->GetFrame());
    animations[DEATH]->SetPart(24, 29);
}
