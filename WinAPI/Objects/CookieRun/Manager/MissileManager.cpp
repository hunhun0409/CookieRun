#include "Framework.h"

MissileManager::MissileManager()
{
    Add("Missile", 20);
}

void MissileManager::Add(string key, UINT size)
{
    vector<GameObject*> missiles(size);

    for (GameObject*& missile : missiles)
    {
        missile = new Missile();
        missile->isActive = false;
    }

    totalObjects[key] = missiles;
}

void MissileManager::Update()
{
    PoolingManager::Update();
    if (isSpawn)
        Spawn();
}


void MissileManager::Render(HDC hdc)
{
    vector<GameObject*> objects = totalObjects["Missile"];

    for (GameObject* object : objects)
    {
        Missile* missile = (Missile*)object;
        missile->CamRender(hdc);
    }
}

void MissileManager::Spawn()
{
    if (spawnTime >= SPAWN_TIME)
    {
        spawnTime = 0.0f;
        elapsedTime = 0.0f;
        isSpawn = false;
    }
    spawnTime += DELTA;
    elapsedTime -= DELTA;

    if (elapsedTime <= 0)
    {
        Missile* missile = (Missile*)Pop("Missile");
        missile->Spawn(Camera::Get()->GetPos() + Vector2(CENTER_X, 0));
        elapsedTime = SPAWN_INTERVAL;
    }
}
