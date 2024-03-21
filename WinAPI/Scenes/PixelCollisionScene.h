#pragma once

class PixelCollisionScene : public Scene
{
public:
    PixelCollisionScene();
    ~PixelCollisionScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    ImageRect* land;
    ImageRect* backGround;

    Megaman* megaman;
};