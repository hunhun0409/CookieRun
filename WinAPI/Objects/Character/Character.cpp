#include "Framework.h"

Character::Character(wstring file, int frameX, int frameY, COLORREF transColor)
{
    texture = Texture::Add(file, frameX, frameY, transColor);

    imageRect = new ImageRect(texture);
}

Character::~Character()
{
    delete imageRect;

    for (pair<int, Animation*> animation : animations)
        delete animation.second;
}

void Character::Update()
{
    imageRect->pos = pos + imageOffset;

    if(animations.count(curType) > 0)
        animations[curType]->Update();
}

void Character::Render(HDC hdc, int alpha)
{
    Rect::LineRender(hdc);

    if (animations.count(curType) == 0)
    {
        imageRect->Render(hdc);
        return;
    }

    if (alpha < 255)
        imageRect->Render(hdc, alpha, animations[curType]->GetFrame());
    else
        imageRect->Render(hdc, animations[curType]->GetFrame());
    
}

void Character::SetAction(int type)
{
    if (curType == type) return;

    curType = type;
    animations[type]->Play();
}
