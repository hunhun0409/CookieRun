#pragma once

class DigGameScene : public Scene
{
public:
    DigGameScene();
    ~DigGameScene();
        
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    virtual void Start() override;
    virtual void End() override;

private:
    ImageRect* land;
    ImageRect* backGround;

    Megaman* megaman;
    Siva* siva;
};