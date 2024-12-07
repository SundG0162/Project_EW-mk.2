#include "pch.h"
#include "WaveManager.h"
#include "SpawnManager.h"
#include "BasicEnemy.h"
#include "SpinEnemy.h"
#include "DashEnemy.h"
#include "InvincibleEnemy.h"

void WaveManager::init()
{

#pragma region spawnData

	//웨이브 0
	waves.push_back({ 3.f, SIvectorforEmpty, EvectorforEmpty });


	//웨이브 1
	waves.push_back({ 8.f, SIvectorforEmpty, getEnemies<BasicEnemy>(1) });

	//웨이브 2
	waves.push_back({ 10.f, SIvectorforEmpty, getEnemies<BasicEnemy>(2) });

	//웨이브 3
	waves.push_back({ 12.f,
		mergeSIVectors(
			getEnemiesInTime<BasicEnemy>(1, 1.0f),
			getEnemiesTimeInterval<SpinEnemy>(2, 2.f)
		),
			getEnemies<DashEnemy>(1) });


#pragma endregion

}



void WaveManager::update()
{
	leftTime -= DELTATIME;
	if (leftTime <= 0)
	{
		//가능하면 시간이 지난다던지 종이 처서 소리가 난다던지 윈도우를 띄어서 메시지를 보내던지 시간이 지났다는걸 표시하고 싶음

		leftTime = waves[++wave].waveContinueTime;
		for (auto enemy : waves[wave].spawnEnemyList)
		{
			GET_SINGLETON(SpawnManager)->addSpawnObject({ enemy, 0.f });
		}
		for (auto info : waves[wave].spawnList)
		{
			GET_SINGLETON(SpawnManager)->addSpawnObject(info);
		}
	}
}
