#include "Framework.h"

Effect::Effect(wstring file, int frameX, int frameY, COLORREF transColor, float speed, bool loop)
    : ImageRect(file, frameX, frameY, transColor)
{
    animation = new Animation(texture->GetFrame(), speed);
    animation->SetDefault(loop);
    animation->SetEndEvent(bind(&Effect::Stop, this));
}

Effect::Effect(Texture* texture, float speed, bool loop)
    : ImageRect(texture)
{
    animation = new Animation(texture->GetFrame(), speed);
    animation->SetDefault(loop);
    animation->SetEndEvent(bind(&Effect::Stop, this));
}

Effect::~Effect()
{
    delete animation;
}

void Effect::Update()
{
    if (!isActive) return;

    animation->Update();
}

void Effect::Render(HDC hdc)
{
    //ImageRect::Render(hdc, animation->GetFrame());
    ImageRect::CamRender(hdc, animation->GetFrame());
}

void Effect::Play(const Vector2& pos)
{
    isActive = true;

    this->pos = pos;
    animation->Play();
}

void Effect::Stop()
{
    isActive = false;
}
