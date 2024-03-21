#include "Framework.h"

Rect::Rect(Vector2 pos, Vector2 size)
    : GameObject(pos), size(size)
{
}

Rect::Rect(float left, float top, float right, float bottom)
{
    pos.x = (left + right) * 0.5f;
    pos.y = (top + bottom) * 0.5f;

    size.x = abs(right - left);
    size.y = abs(bottom - top);

}

void Rect::Render(HDC hdc)
{
    if (!isActive)
        return;

    int left = (int)(pos.x - size.x * 0.5f);
    int right = (int)(pos.x + size.x * 0.5f);
    int top = (int)(pos.y - size.y * 0.5f);
    int bottom = (int)(pos.y + size.y * 0.5f);

    Rectangle(hdc, left, top, right, bottom);
}

void Rect::LineRender(HDC hdc)
{
    if (!isActive)
        return;

    MoveToEx(hdc, (int)Left(), (int)Top(), nullptr);
    LineTo(hdc, (int)Left(), (int)Bottom());

    MoveToEx(hdc, (int)Left(), (int)Bottom(), nullptr);
    LineTo(hdc, (int)Right(), (int)Bottom());

    MoveToEx(hdc, (int)Right(), (int)Top(), nullptr);
    LineTo(hdc, (int)Right(), (int)Bottom());

    MoveToEx(hdc, (int)Left(), (int)Top(), nullptr);
    LineTo(hdc, (int)Right(), (int)Top());
}

void Rect::CamLineRender(HDC hdc)
{
    if (!isActive)
        return;
    
    Rect CamRect;
    CamRect.size = size;
    CamRect.pos = pos - Camera::Get()->GetPos();

    MoveToEx(hdc, (int)CamRect.Left(), (int)CamRect.Top(), nullptr);
    LineTo(hdc, (int)CamRect.Left(), (int)CamRect.Bottom());

    MoveToEx(hdc, (int)CamRect.Left(), (int)CamRect.Bottom(), nullptr);
    LineTo(hdc, (int)CamRect.Right(), (int)CamRect.Bottom());

    MoveToEx(hdc, (int)CamRect.Right(), (int)CamRect.Top(), nullptr);
    LineTo(hdc, (int)CamRect.Right(), (int)CamRect.Bottom());

    MoveToEx(hdc, (int)CamRect.Left(), (int)CamRect.Top(), nullptr);
    LineTo(hdc, (int)CamRect.Right(), (int)CamRect.Top());
}

bool Rect::IsCollision(const Vector2& point) const
{
    if (!isActive)
        return false;

    if (point.x > Left() && point.x < Right())
    {
        if (point.y > Top() && point.y < Bottom())
            return true;
    }

    return false;
}

bool Rect::IsRectCollision(const Rect* rect) const
{
    if (!isActive) return false;
    if (!rect->isActive) return false;

    if (rect->Left() < Right() && rect->Right() > Left())
    {
        if (rect->Top() < Bottom() && rect->Bottom() > Top())
        {
            return true;
        }
    }

    return false;
}

bool Rect::IsRectCollision(IN const Rect* rect, OUT Vector2* overlapSize) const
{
    if (!isActive) return false;
    if (!rect->isActive) return false;

    float left = max(rect->Left(), Left());
    float right = min(rect->Right(), Right());
    float top = max(rect->Top(), Top());
    float bottom = min(rect->Bottom(), Bottom());

    overlapSize->x = right - left;
    overlapSize->y = bottom - top;

    if (overlapSize->x > 0 && overlapSize->y > 0)
        return true;

    return false;
}

bool Rect::IsCircleCollision(const Circle* circle) const
{
    if (!isActive) return false;
    if (!circle->isActive) return false;

    //십자가 범위
    if (circle->pos.x > Left() && circle->pos.x < Right() ||
        circle->pos.y > Top() && circle->pos.y < Bottom())
    {
        Vector2 size(circle->GetRadius() * 2, circle->GetRadius() * 2);
        Rect temp(circle->pos, size);

        if (IsRectCollision(&temp))
            return true;
        else
            return false;
    }

    //십자가 밖 범위(대각선 범위)
    Vector2 edges[4];
    edges[0] = { Left(), Top() };
    edges[1] = { Left(), Bottom() };
    edges[2] = { Right(), Top() };
    edges[3] = { Right(), Bottom() };

    for (Vector2 edge : edges)
    {
        if (circle->IsCollision(edge))
            return true;
    }

    return false;
}

bool Rect::IsLineCollision(const Line* line) const
{
    return false;
}
