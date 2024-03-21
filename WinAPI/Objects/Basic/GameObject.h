#pragma once

class Line;
class Rect;
class Circle;

class GameObject
{
public:
    GameObject() = default;
    GameObject(Vector2 pos) : pos(pos) {}
    ~GameObject() = default;

    virtual void Update() {}
    virtual void Render(HDC hdc) = 0;

    virtual bool IsCollision(const GameObject* object);

    virtual bool IsCollision(const Vector2& point) const = 0;
    virtual bool IsRectCollision(const Rect* rect) const = 0;
    virtual bool IsCircleCollision(const Circle* circle) const = 0;
    virtual bool IsLineCollision(const Line* line) const = 0;


    virtual bool IsRectCollision(IN const Rect* rect, OUT Vector2* overlapSize) const { return false; }

public:
    string tag;
    bool isActive = true;
    Vector2 pos;
};