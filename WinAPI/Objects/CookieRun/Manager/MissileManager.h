#pragma once
class MissileManager : public PoolingManager, public Singleton<MissileManager>
{
private:
	const float SPAWN_INTERVAL = 0.3f;
	const float SPAWN_TIME = 5.0f;
private:
	friend class Singleton;
	MissileManager();
	~MissileManager() = default;

public:
	void Add(string key, UINT size);
	
	void Update();
	void Render(HDC hdc);

	void Spawn();

	void SetOwner(GameObject* owner) { this->owner = owner; }

	bool& IsSpawn() { return isSpawn; }
private:
	bool isSpawn = false;
	float spawnTime = 0.0f;
	float elapsedTime = 0.0f;

	GameObject* owner;
};
