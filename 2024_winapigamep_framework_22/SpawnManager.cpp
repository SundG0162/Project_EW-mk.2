#include "pch.h"
#include "SpawnManager.h"
#include "Scene.h"
#include "EventManager.h"
#include "TimeManager.h"
#include "PlayerManager.h"
#include "Enemy.h"

void SpawnManager::init()
{
	currentTime = 0;
	//_target = (Object*)GET_SINGLETON(PlayerManager)->getPlayer();
}

void SpawnManager::update()
{
	if (_target == nullptr)
	{
		_target = (Object*)GET_SINGLETON(PlayerManager)->getPlayer();
		return;
	}
	if (spawnQueue.empty())return;
	SpawnInfo topInfo = spawnQueue.front();
	currentTime += DELTATIME;
	if (topInfo.spawnTime < currentTime)
	{
		GET_SINGLETON(EventManager)->createObject(topInfo.spawnTarget, LAYER::ENEMY);
		Enemy* spawningObject;
		if(spawningObject = dynamic_cast<Enemy*>(topInfo.spawnTarget))
			spawningObject->SetTarget(_target);
		spawnQueue.pop();
	}
}
