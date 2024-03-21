#pragma once

class Character : public Rect
{
protected:
    const float JUMP_POWER = 700.0f;
    const float GRAVITY = 1500.0f;

public:
    Character(wstring file, int frameX, int frameY, COLORREF transColor = MAGENTA);
    ~Character();

    virtual void Update();
    virtual void Render(HDC hdc, int alpha = 255);    

protected:
    void SetAction(int type);

protected:
    Texture* texture;

    ImageRect* imageRect;
    Vector2 imageOffset;

    map<int, Animation*> animations;

    int curType = 0;
};