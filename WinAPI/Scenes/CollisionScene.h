#pragma once

class CollisionScene : public Scene
{
public:
    CollisionScene();
    ~CollisionScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    vector<GameObject*> objects;

    HBRUSH hRedBrush;
    HBRUSH hBlueBrush;

    HPEN hRedPen;
    HPEN hBluePen;

    bool isCollision = false;
};