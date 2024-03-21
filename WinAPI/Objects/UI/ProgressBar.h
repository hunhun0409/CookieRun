#pragma once

class ProgressBar : public Rect
{
public:
    ProgressBar(Texture* frontTexture, Texture* backTexture = nullptr);
    ~ProgressBar();

    void Render(HDC hdc);

    void SetValue(const float& value) { this->value = value; }

    Vector2& BackOffset() { return backOffset; }

private:
    Texture* frontTexture;
    Texture* backTexture;

    Vector2 backSize = {};
    Vector2 backOffset = {};

    float value;
};