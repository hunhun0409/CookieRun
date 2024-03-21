#include "Framework.h"

Button::Button(wstring file)
    : ImageRect(file)
{
    normalTexture = texture;
    normalSize = size;
    downSize = size * 0.95f;
    overSize = size * 1.05f;
}

Button::Button(Texture* texture)
    : ImageRect(texture), normalTexture(texture)
{
    normalSize = size;
    downSize = size * 0.95f;
    overSize = size * 1.05f;
}

Button::~Button()
{
}

void Button::Update()
{
    if (!isActive) return;

    if (IsCollision(mousePos))
    {
        state = OVER;

        if (KEY_UP(VK_LBUTTON) && isLClick)
        {
            if (leftClickEvent)
                leftClickEvent();
            isLClick = false;
        }

        if (KEY_DOWN(VK_LBUTTON))
        {
            isLClick = true;
        }

        if (KEY_PRESS(VK_LBUTTON))
        {
            state = DOWN;
        }

        if (KEY_UP(VK_RBUTTON) && isRClick)
        {
            if (rightClickEvent)
                rightClickEvent();
            isRClick = false;
        }

        if (KEY_DOWN(VK_RBUTTON))
        {
            isLClick = true;

            isRClick = true;
        }

        if (KEY_PRESS(VK_RBUTTON))
        {
            state = DOWN;
        }

    }
    else
    {
        state = NORMAL;

        if (KEY_UP(VK_LBUTTON))
            isLClick = false;
        if (KEY_UP(VK_RBUTTON))
            isLClick = false;
    }


    switch (state)
    {
    case Button::NORMAL:
        texture = normalTexture;
        size = normalSize;
        break;
    case Button::OVER:
        if(overTexture)
            texture = overTexture;
        size = overSize;
        break;
    case Button::DOWN:
        if(downTexture)
            texture = downTexture;
        size = downSize;
        break;
    default:
        break;
    }

}

void Button::Render(HDC hdc)
{
    ImageRect::Render(hdc);

    if (font)
    {
        oldFont = (HFONT)SelectObject(hdc, font);
    }

    COLORREF oldColor = SetTextColor(hdc, fontColor);

    RECT rect = { Left() + offset.x, Top() + offset.y,
        Right() - offset.x, Bottom() - offset.y };
    DrawTextA(hdc, text.c_str(), text.length(), &rect, DT_CENTER);

    if (font)
        SelectObject(hdc, oldFont);

    SetTextColor(hdc, oldColor);
}

void Button::SetFont(HFONT font, int fontSize, COLORREF fontColor)
{
    this->font = font;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
}
