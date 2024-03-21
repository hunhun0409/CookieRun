#include "Framework.h"

PixelCharacter::PixelCharacter(wstring file, int frameX, int frameY)
    : ImageRect(file, frameX, frameY)
{
}

PixelCharacter::~PixelCharacter()
{
    for (pair<int, Animation*> animation : animations)
        delete animation.second;
}

void PixelCharacter::Update()
{    
    Jump();    

    animations[curType]->Update();
}

void PixelCharacter::Render(HDC hdc)
{
    ImageRect::CamRender(hdc, animations[curType]->GetFrame());
}

void PixelCharacter::Jump()
{
    velocity.y -= GRAVITY * DELTA;
    pos.y -= velocity.y * DELTA;

    Vector2 bottomPos = pos;
    bottomPos.y = Bottom() - 20.0f;

    float height = landTexture->GetPixelHeight(bottomPos);

    if (Bottom() > height)
    {
        if (velocity.y < 0.0f)
        {
            velocity.y = 0.0f;
            jumpCount = 0;
            pos.y = height - Half().y;
        }
    }
}

void PixelCharacter::SetAction(int type)
{
    if (curType == type) return;

    curType = type;
    animations[type]->Play();
}

bool PixelCharacter::CanMove()
{
    Vector2 nextPos = pos;
    nextPos.y = Top();

    if (velocity.x > 0)
        nextPos.x += CHECK_DIST;
    else if (velocity.x < 0)
        nextPos.x -= CHECK_DIST;

    float nextHeight = landTexture->GetPixelHeight(nextPos);

    float slope = Bottom() - nextHeight;

    if (slope > MAX_SLOPE)
        return false;

    return true;
}
