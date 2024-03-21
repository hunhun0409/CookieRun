#pragma once

class BombManager : public PoolingManager, public Singleton<BombManager>
{
private:
    friend class Singleton;

    BombManager();
    ~BombManager();

public:
    void Plant(const Vector2& pos);
    void SetLand(Texture* texture);

    void Clear();

private:
    virtual void CreateObjects(string key, UINT poolSize) override;

private:
    HBRUSH hBrush;
    HPEN hPen;
};