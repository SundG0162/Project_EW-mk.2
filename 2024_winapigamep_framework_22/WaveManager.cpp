#include "pch.h"
#include "WaveManager.h"
#include "SpawnManager.h"
#include "BasicEnemy.h"
#include "SpinEnemy.h"
#include "DashEnemy.h"
#include "InvincibleEnemy.h"

void WaveManager::init()
{
	static vector<SpawnInfo> SIvectorforEmpty;
	static vector<Enemy> EvectorforEmpty;

#pragma region spawnData

	//웨이브 0
	waves.push_back({ 3.f, SIvectorforEmpty, EvectorforEmpty });


	//웨이브 1
	waves.push_back({ 10.f, SIvectorforEmpty, getAllocEnemies<BasicEnemy>(1) });

	//웨이브 2
	waves.push_back({ 10.f, SIvectorforEmpty, getAllocEnemies<BasicEnemy>(2) });

	waves.push_back({ 12.f,
		mergeVectors(
			getAllocEnemyInterval<DashEnemy>(2, 1f),
			getAllocEnemies<BasicEnemy>(2, 1.5f)
		), EvectorforEmpty;
		});
#pragma endregion

}

SpawnManager* sm = GET_SINGLETON(SpawnManager);

void WaveManager::update()
{
	leftTime -= DELTATIME;
	if (leftTime <= 0)
	{
		//가능하면 시간이 지난다던지 종이 처서 소리가 난다던지 윈도우를 띄어서 메시지를 보내던지 시간이 지났다는걸 표시하고 싶음

		leftTime = waves[++wave];
		for (auto enemy : waves[wave].spawnEnemyList)
		{
			sm->addSpawnObject({ enemy, 0.f });
		}
		for (auto info : waves[wave].spawnList)
		{
			sm->addSpawnObject(info);
		}
	}
}
