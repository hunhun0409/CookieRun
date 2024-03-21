#pragma once

class Line : public GameObject
{
public:
    Line() = default;
    Line(Vector2 start, Vector2 end);

    virtual void Render(HDC hdc) override;

    virtual bool IsCollision(const Vector2& point) const override;
    virtual bool IsRectCollision(const Rect* rect) const override;
    bool IsRectCollision(const Rect* rect, Vector2& collisionPoint);

    virtual bool IsCircleCollision(const Circle* circle) const override;
    bool IsCircleCollision(const Circle* circle, Vector2& closestPoint);

    virtual bool IsLineCollision(const Line* line) const override;
    bool IsLineCollision(const Line* line, Vector2& crossPoint);
    bool IsBetweenLine(const Line* line)const;


public:
    Vector2 end;

};