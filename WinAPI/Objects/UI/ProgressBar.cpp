#include "Framework.h"

ProgressBar::ProgressBar(Texture* frontTexture, Texture* backTexture)
    : frontTexture(frontTexture), backTexture(backTexture)
{
    size = frontTexture->GetSize();
    backSize = backTexture->GetSize();
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Render(HDC hdc)
{
    if (backTexture)
    {
        Rect rect;
        rect.pos = pos + backOffset;
        rect.size = backSize;
        backTexture->Render(hdc, &rect);
    }
        

    GdiTransparentBlt(
        hdc,
        (int)Left(), (int)Top(),
        (int)(size.x * value), (int)size.y,
        frontTexture->GetMemDC(),
        0, 0, (int)(size.x * value), (int)size.y,
        MAGENTA
    );
}
