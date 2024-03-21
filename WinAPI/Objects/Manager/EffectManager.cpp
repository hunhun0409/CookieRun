#include "Framework.h"

void EffectManager::Play(string key, Vector2 pos)
{
    Effect* effect = (Effect*)Pop(key);
    effect->Play(pos);
}

void EffectManager::Add(string key, UINT poolSize, wstring file, int frameX, int frameY, COLORREF transColor, float speed, bool loop)
{
    if (totalObjects.count(key) > 0)
        return;

    Texture* texture = Texture::Add(file, frameX, frameY, transColor);

    vector<GameObject*> effects(poolSize);

    for (GameObject*& effect : effects)
    {
        effect = new Effect(texture, speed, loop);
        effect->isActive = false;
    }

    totalObjects[key] = effects;
}

void EffectManager::Add(string key, UINT poolSize, Texture* texture, float speed, bool loop)
{
    if (totalObjects.count(key) > 0)
        return;

    vector<GameObject*> effects(poolSize);

    for (GameObject*& effect : effects)
    {
        effect = new Effect(texture, speed, loop);
        effect->isActive = false;
    }

    totalObjects[key] = effects;
}
