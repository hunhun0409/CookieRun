#pragma once

class PixelCharacter : public ImageRect
{
protected:
    const float JUMP_POWER = 500.0f;
    const float GRAVITY = 980.0f;
    const float CHECK_DIST = 30.0f;
    const float MAX_SLOPE = 40.0f;

public:
    PixelCharacter(wstring file, int frameX, int frameY);
    ~PixelCharacter();

    void Update();
    void Render(HDC hdc);

    void SetLand(Texture* texture) { landTexture = texture; }

protected:
    void Jump();
    void SetAction(int type);
    bool CanMove();

protected:
    map<int, Animation*> animations;

    int curType = 0;

    Vector2 velocity;

    float speed = 200.0f;

    UINT jumpCount = 0;

    Texture* landTexture;
};