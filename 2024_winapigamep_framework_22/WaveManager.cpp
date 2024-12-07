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

	//���̺� 0
	waves.push_back({ 3.f, SIvectorforEmpty, EvectorforEmpty });


	//���̺� 1
	waves.push_back({ 8.f, SIvectorforEmpty, getEnemies<BasicEnemy>(1) });

	//���̺� 2
	waves.push_back({ 10.f, SIvectorforEmpty, getEnemies<BasicEnemy>(2) });

	//���̺� 3
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
		//�����ϸ� �ð��� �����ٴ��� ���� ó�� �Ҹ��� ���ٴ��� �����츦 �� �޽����� �������� �ð��� �����ٴ°� ǥ���ϰ� ����

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
