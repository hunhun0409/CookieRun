#include "Framework.h"

Line::Line(Vector2 start, Vector2 end)
    : GameObject(start), end(end)
{
}

void Line::Render(HDC hdc)
{
    MoveToEx(hdc, pos.x, pos.y, nullptr);
    LineTo(hdc, end.x, end.y);
}

bool Line::IsCollision(const Vector2& point) const
{
    return false;
}

bool Line::IsRectCollision(const Rect* rect) const
{
    Line a, b, c, d;
    a.pos = { rect->Left(), rect->Top() };
    b.pos = { rect->Right(), rect->Top() };
    c.pos = { rect->Right(), rect->Bottom() };
    d.pos = { rect->Left(), rect->Bottom() };

    a.end = b.pos;
    b.end = c.pos;
    c.end = d.pos;
    d.end = a.pos;

    if (IsLineCollision(&a) || IsLineCollision(&b) || IsLineCollision(&c) || IsLineCollision(&d))
        return true;
    else
        return false;
}

bool Line::IsRectCollision(const Rect* rect, Vector2& collisionPoint)
{
    if (rect->IsCollision(pos) || rect->IsCollision(end)) return true;

    Line top, right, bottom, left;
    top.pos = { rect->Left(), rect->Top() };
    right.pos = { rect->Right(), rect->Top() };
    bottom.pos = { rect->Right(), rect->Bottom() };
    left.pos = { rect->Left(), rect->Bottom() };

    top.end = right.pos;
    right.end = bottom.pos;
    bottom.end = left.pos;
    left.end = top.pos;

    Vector2 tempPos1, tempPos2, tempPos3, tempPos4;


    if (IsLineCollision(&left))
    {
        IsLineCollision(&left, collisionPoint);
        return true;
    }
    if (IsLineCollision(&top))
    {
        IsLineCollision(&top, collisionPoint);
        return true;
    }
    if (IsLineCollision(&right))
    {
        IsLineCollision(&right, collisionPoint);
        return true;
    }
    if (IsLineCollision(&bottom))
    {
        IsLineCollision(&bottom, collisionPoint);
        return true;
    }
    
    return false;
}

bool Line::IsCircleCollision(const Circle* circle) const
{
    Vector2 A = circle->pos - pos;
    Vector2 B = end - pos;

    float dot = Dot(A, B.GetNormalized());

    dot = Clamp(0.0f, B.Length(), dot);

    Vector2 closestPoint = pos + B.GetNormalized() * dot;

    return circle->IsCollision(closestPoint);
}

bool Line::IsCircleCollision(const Circle* circle, Vector2& closestPoint)
{
    Vector2 A = circle->pos - pos;
    Vector2 B = end - pos;

    float dot = Dot(A, B.GetNormalized());

    dot = Clamp(0.0f, B.Length(), dot);

    closestPoint = pos + B.GetNormalized() * dot;

    return circle->IsCollision(closestPoint);
}

bool Line::IsLineCollision(const Line* line) const
{
    return IsBetweenLine(line) && line->IsBetweenLine(this);
}

bool Line::IsLineCollision(const Line* line, Vector2& crossPoint)
{
    float t;
    float s;

    float under = (line->end.y - line->pos.y) * (end.x - pos.x) - (line->end.x - line->pos.x) * (end.y - pos.y);
    if (under == 0) return false;

    float _t = (line->end.x - line->pos.x) * (pos.y - line->pos.y) - (line->end.y - line->pos.y) * (pos.x - line->pos.x);
    float _s = (end.x - pos.x) * (pos.y - line->pos.y) - (end.y - pos.y) * (pos.x - line->pos.x);

    t = _t / under;
    s = _s / under;

    if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
    if (_t == 0 && _s == 0) return false;

    crossPoint.x = pos.x + t * (float)(end.x - pos.x);
    crossPoint.y = pos.y + t * (float)(end.y - pos.y);

    return true;
}

bool Line::IsBetweenLine(const Line* line) const
{
    Vector2 e1 = line->pos - pos;
    Vector2 e2 = line->end - pos;
    Vector2 e3 = end - pos;

    return Cross(e1, e3) * Cross(e2, e3) < 0;
}
