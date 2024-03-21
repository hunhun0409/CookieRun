#include "Framework.h"

Camera::Camera()
{
    rect = new Rect({}, { WIN_WIDTH, WIN_HEIGHT });
}

Camera::~Camera()
{
    delete rect;
}

void Camera::Update()
{
    if (target)
        FollowMode();
    else
        FreeMove();

    if(isShake)
        Shake();
}

Vector2 Camera::GetPos()
{
    return rect->pos;
}

void Camera::SetPos(Vector2 pos)
{
    rect->pos = pos - rect->Half() - offset;

    FixPos(rect->pos);

}

void Camera::SetPos(float x, float y)
{
    rect->pos.x = x - rect->Half().x - offset.x;
    rect->pos.y = y - rect->Half().y - offset.y;

    FixPos(rect->pos);
}

float Camera::Left()
{
    return rect->pos.x;
}

float Camera::Right()
{
    return rect->pos.x + rect->size.x;
}

float Camera::Top()
{
    return rect->pos.y;
}

float Camera::Bottom()
{
    return rect->pos.y + rect->size.y;
}

void Camera::CameraShake(float time, float range)
{
    isShake = true;
    shakeTime = time;
    shakeRange = range;
}


void Camera::FreeMove()
{
    if (KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS('A'))
            rect->pos.x -= moveSpeed * DELTA;
        if (KEY_PRESS('D'))
            rect->pos.x += moveSpeed * DELTA;
        if (KEY_PRESS('W'))
            rect->pos.y -= moveSpeed * DELTA;
        if (KEY_PRESS('S'))
            rect->pos.y += moveSpeed * DELTA;

        FixPos(rect->pos);
    }
}

void Camera::FollowMode()
{
    //destPos = target->pos - rect->Half() - offset;
    destPos = {target->pos.x - rect->Half().x - offset.x, rect->pos.y};


    FixPos(destPos);

    //rect->pos = destPos;
    rect->pos = Lerp(rect->pos, destPos, followSpeed * DELTA);
    
    
}

void Camera::FixPos(Vector2& pos)
{
    if (mapRect == nullptr) return;

    if (pos.x < mapRect->Left())
        pos.x = mapRect->Left();

    if (pos.y < mapRect->Top())
        pos.y = mapRect->Top();

    if (pos.x + rect->size.x > mapRect->Right())
        pos.x = mapRect->Right() - rect->size.x;

    if (pos.y + rect->size.y > mapRect->Bottom())
        pos.y = mapRect->Bottom() - rect->size.y;
}

void Camera::Shake()
{
    shakeInterval += DELTA;
    shakeTime -= DELTA;

    if (shakeTime <= 0.0f)
    {
        isShake = false;
        return;
    }
    if (shakeInterval >= SHAKE_INTERVAL)
    {
        float shakeX = Random(-shakeRange, shakeRange);

        rect->pos.x += shakeX;

        shakeInterval = 0.0f;
    }
}
