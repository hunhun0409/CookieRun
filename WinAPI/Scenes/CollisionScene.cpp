#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
    hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

    hRedPen = CreatePen(PS_SOLID, 5, RED);
    hBluePen = CreatePen(PS_SOLID, 5, BLUE);

    Vector2 center(CENTER_X, CENTER_Y);

    objects.push_back(new Line(Vector2(50, 50), Vector2(50, 50)));
    //objects.push_back(new Line(Vector2(700, 50), Vector2(50, 600)));    
    objects.push_back(new Circle({100, 100}, 5));
    //objects.push_back(new Circle(center, 30));
    objects.push_back(new Rect(center, { 50, 50 }));
}

CollisionScene::~CollisionScene()
{
    DeleteObject(hRedBrush);
    DeleteObject(hBlueBrush);

    DeleteObject(hRedPen);
    DeleteObject(hBluePen);

    for (GameObject* object : objects)
        delete object;
}

void CollisionScene::Update()
{
    ((Line*)objects[0])->end = mousePos;

    //선끼리 충돌처리
    //isCollision = objects[0]->IsCollision(objects[1]);
    //((Line*)objects[0])->IsLineCollision((Line*)objects[1], objects[2]->pos);

    //선과 원의 충돌
    isCollision = objects[0]->IsCollision(objects[2]);
    ((Line*)objects[0])->IsRectCollision((Rect*)objects[2], objects[1]->pos);





    /*
    Vector2 overlapSize;
    if (objects[0]->IsRectCollision((Rect*)objects[1], &overlapSize))
    {
        if (overlapSize.x > overlapSize.y)//상하 충돌
        {
            if (objects[0]->pos.y > objects[1]->pos.y)
            {
                objects[1]->pos.y -= overlapSize.y;
            }
            else
            {
                objects[1]->pos.y += overlapSize.y;
            }
        }
        else//좌우 충돌
        {
            if (objects[0]->pos.x > objects[1]->pos.x)
            {
                objects[1]->pos.x -= overlapSize.x;
            }
            else
            {
                objects[1]->pos.x += overlapSize.x;
            }
        }
    }
    */
}

void CollisionScene::Render(HDC hdc)
{
    if (isCollision)
    {
        SelectObject(hdc, hRedBrush);
        SelectObject(hdc, hRedPen);
    }
    else
    {
        SelectObject(hdc, hBlueBrush);
        SelectObject(hdc, hBluePen);
    }

    for (GameObject* object : objects)
    {
        object->Render(hdc);
    }
        
}
