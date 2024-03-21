#pragma once

class Monster : public BattleCharacter
{
private:
    enum ActionType
    {
        IDLE, RUN, ATTACK,
        HIT, DEATH
    };

    enum class State
    {
        PARTROL, TRACE,
        ATTACK, HIT, DEATH
    };
    
    const float TRACE_RANGE = 300.0f;    
    const float PATROL_RANGE = 200.0f;

public:
    Monster();
    ~Monster();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void Damage();

    void SetTarget(GameObject* target) { this->target = target; }
private:
    virtual void Move() override;

    void SetState();
    void ActionState();
    void SetAnimation();

    void Patrol();
    void Trace();
    void Attack();
    void EndAttack();
    void Hit();
    void Death();

    void CreateAnimations();

private:
    State state;

    GameObject* target;

    GameObject* traceRange;
    GameObject* attackRange;

    Vector2 destPos;
    float speed = 100.0f;

    ProgressBar* hpBar;

    float maxHp = 100.0f;
    float curHp = 100.0f;
};