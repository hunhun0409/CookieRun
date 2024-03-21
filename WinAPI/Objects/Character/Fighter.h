#pragma once

class Fighter : public BattleCharacter
{
private:
    enum ActionType
    {
        IDLE, WALK, RUN, PUNCH, KICK,
        JUMP, JUMP_ATTACK
    };

    const float WALK_SPEED = 100.0f;
    const float RUN_SPEED = 200.0f;
    const float RUN_TOUCH_DELAY = 0.5f;

public:
    Fighter();
    ~Fighter();

    virtual void Update() override;    

private:
    void Control();    
    void Attack();    
    void SetAnimation();

    void CreateAnimations();
    
    void CheckMoveTouchTime();
private:   
    bool isRun = false;
    bool isMoveTouch = false;
    

    float touchTime = 0.0f;
};