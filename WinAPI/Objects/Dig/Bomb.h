#pragma once

class Bomb : public ImageRect
{
private:
    const float EXP_TIME = 4.0f;
    const float EXP_RANGE = 100.0f;
    const float GRAVITY = 980.0f;

public:
    Bomb();
    ~Bomb();

    void Update();
    void Render(HDC hdc);

    void Plant(const Vector2& pos);

    void SetLandTexture(Texture* texture) { landTexture = texture; }
    void SetBrush(HBRUSH brush, HPEN pen) { hBrush = brush, hPen = pen; }

private:
    void Fall();
    void Timer();

private:
    float time = 0.0f;
    float velocity = 0.0f;

    Texture* landTexture;

    HBRUSH hBrush;
    HPEN hPen;
};