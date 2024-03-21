#include "Framework.h"

Circle::Circle(Vector2 pos, float radius)
    : GameObject(pos), radius(radius)
{
}

void Circle::Render(HDC hdc)
{
    if (!isActive)
        return;

    int left = (int)(pos.x - radius);
    int right = (int)(pos.x + radius);
    int top = (int)(pos.y - radius);
    int bottom = (int)(pos.y + radius);

    Ellipse(hdc, left, top, right, bottom);
}

bool Circle::IsCollision(const Vector2& point) const
{
    if (!isActive) return false;

    //float x = pos.x - point.x;
    //float y = pos.y - point.y;
    //
    //float distance = sqrt(x * x + y * y);

    float distance = (point - pos).Length();

    return distance < radius;
}

bool Circle::IsCircleCollision(const Circle* circle) const
{
    if (!isActive) return false;
    if (!circle->isActive) return false;

    float distance = (circle->pos - pos).Length();

    return distance < (radius + circle->radius);
}

bool Circle::IsRectCollision(const Rect* rect) const
{
    return rect->IsCircleCollision(this);
}

bool Circle::IsLineCollision(const Line* line) const
{
    return false;
}
