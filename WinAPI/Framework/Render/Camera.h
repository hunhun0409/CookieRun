#pragma once

class Rect;
class GameObject;

class Camera : public Singleton<Camera>
{
private:
    const float SHAKE_INTERVAL = 0.02f;
private:
    friend class Singleton;

    Camera();
    ~Camera();
public:
    void Update();

    void SetTarget(GameObject* target) { this->target = target; }
    void SetOffset(const float& x, const float& y) { offset = { x, y }; }
    void SetMapRect(Rect* rect) { mapRect = rect; }

    Vector2 GetPos();

    void SetPos(Vector2 pos);
    void SetPos(float x, float y);

    float Left();
    float Right();
    float Top();
    float Bottom();

    void CameraShake(float time = 0.2f, float range = 10.0f);

private:
    void FreeMove();
    void FollowMode();

    void FixPos(Vector2& pos);

    void Shake();
private:
    Rect* rect;
    float moveSpeed = 200.0f;
    float followSpeed = 20.0f;

    GameObject* target = nullptr;

    Vector2 offset;
    Vector2 destPos;

    Rect* mapRect = nullptr;

    bool isShake = false;
    float shakeTime = 0.0f;
    float shakeInterval = SHAKE_INTERVAL;
    float shakeRange = 0.0f;
};