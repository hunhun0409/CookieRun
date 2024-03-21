#pragma once

class Megaman : public PixelCharacter
{
private:
    enum ActionType
    {
        IDLE, RUN, JUMP_UP, JUMP_DOWN, PLANT
    };

public:
    Megaman();
    ~Megaman();

    void Update();        

private:
    void Move();
    void Plant();
    void Control();    
    void SetAnimation();

    void SetIdle();
    void CreateAnimations();
};