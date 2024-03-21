#pragma once

class BattleScene : public Scene
{
public:
    BattleScene();
    ~BattleScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    virtual void Start() override;
    virtual void End() override;

private:
    Fighter* fighter;
    Monster* monster;
};