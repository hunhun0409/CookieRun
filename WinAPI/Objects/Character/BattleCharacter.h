#pragma once

class BattleCharacter : public Character
{
public:
    BattleCharacter(wstring file, int frameX, int frameY, COLORREF transColor = MAGENTA);
    ~BattleCharacter();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    Rect* GetAttackCollider() { return attackCollider; }

protected:    
    virtual void Move();    
    void EndAttack();    

protected:    
    Vector2 velocity;

    bool isAttack = false;

    Rect* attackCollider;
};