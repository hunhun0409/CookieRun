#pragma once

class Effect : public ImageRect
{
public:
    Effect(wstring file, int frameX, int frameY, COLORREF transColor,
        float speed = 1.0f, bool loop = false);
    Effect(Texture* texture, float speed = 1.0f, bool loop = false);
    ~Effect();

    void Update();
    void Render(HDC hdc);

    void Play(const Vector2& pos);
    void Stop();

private:
    Animation* animation;
};