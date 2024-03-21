#include "Framework.h"

BattleCharacter::BattleCharacter(wstring file, int frameX, int frameY, COLORREF transColor)
    : Character(file, frameX, frameY, transColor)
{
    attackCollider = new Rect();
    attackCollider->isActive = false;    
}

BattleCharacter::~BattleCharacter()
{
    delete attackCollider;
}

void BattleCharacter::Update()
{    
    Move();   

    Character::Update();
}

void BattleCharacter::Render(HDC hdc)
{
    Character::Render(hdc);
    attackCollider->LineRender(hdc);
}

void BattleCharacter::Move()
{
    if (isAttack) return;

    pos += velocity * DELTA;
}

void BattleCharacter::EndAttack()
{
    isAttack = false;
    SetAction(0);
    attackCollider->isActive = false;
}