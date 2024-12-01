#pragma once
class Object;
struct SpawnInfo
{
	Object* spawnTarget;
	float spawnTime;
};
class SpawnManager
{
	DECLARE_SINGLETON(SpawnManager);
public:
	void init();
	void update();
	const void addSpawnObject(SpawnInfo& info) { spawnQueue.push(info); }
private:
	std::queue<SpawnInfo> spawnQueue;
	float currentTime;
};

