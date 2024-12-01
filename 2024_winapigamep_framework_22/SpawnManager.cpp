#include "pch.h"
#include "SpawnManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TimeManager.h"

void SpawnManager::init()
{
	currentTime = 0;
}

void SpawnManager::update()
{
	if (spawnQueue.empty())return;
	SpawnInfo topInfo = spawnQueue.front();
	currentTime += DELTATIME;
	if (topInfo.spawnTime < currentTime)
	{
		cout << "spawned" << endl;
		GET_SINGLETON(SceneManager)->getCurrentScene()->addObject(topInfo.spawnTarget, LAYER::UI);
		spawnQueue.pop();
	}
}
