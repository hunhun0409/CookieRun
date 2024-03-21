#pragma once

class Siva : public PixelCharacter
{
private:
    enum ActionType
    {
        IDLE_LEFT, IDLE_RIGHT,
        RUN_LEFT, RUN_RIGHT
    };

    enum State
    {
        PATROL, IDLE, HIT
    };

    const float SPEED = 200.0f;
    const float PATROL_TIME = 2.0f;
    const float IDLE_TIME = 1.0f;
    const float HIT_TIME = 2.0f;
    const float BLINK_SPEED = 500.0f;

public:
    Siva();
    ~Siva();

    void Update();
    void Render(HDC hdc);

    void Damage(void* bomb);

private:
    void ActionState();
    void Patrol();    
    void Hit();
    void Idle();    

    void StartPatrol();

private:
    void CreateAnimations();

private:
    State state = IDLE;

    float alphaValue = 255;
    bool isIncreaseAlpha = false;

    float idleTime = 0.0f;
    float patrolTime = 0.0f;    
    float hitTime = 0.0f;
};