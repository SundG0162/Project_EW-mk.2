#include "pch.h"
#include "WaveManager.h"
#include "SpawnManager.h"
#include "BasicEnemy.h"
#include "SpinEnemy.h"
#include "DashEnemy.h"
#include "InvincibleEnemy.h"
#include <iostream>

void WaveManager::init()
{

#pragma region spawnData

	//���̺� 0
	waves.push_back({ 3.f, SIvectorforEmpty, EvectorforEmpty });


	//���̺� 1
	waves.push_back({ 6.f, SIvectorforEmpty, getEnemies<BasicEnemy>(1) });

	//���̺� 2
	waves.push_back({ 8.f, SIvectorforEmpty, getEnemies<BasicEnemy>(2) });

	//���̺� 3
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<BasicEnemy>(1, 1.0f),
			getEnemiesTimeInterval<SpinEnemy>(3, 0.5f)
		),
			EvectorforEmpty });
	//���̺� 4
	waves.push_back({ 10.f,
		SIvectorforEmpty,
		getEnemies<DashEnemy>(3) });
	//���̺� 5
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<SpinEnemy>(2, 2.f)
		),
			EvectorforEmpty });
	//���̺� 6
	waves.push_back({ 10.f,
		SIvectorforEmpty,getEnemies<InvincibleEnemy>(1) });
	//���̺� 7
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<InvincibleEnemy>(2, 1.f)
		),
			EvectorforEmpty });
	//���̺� 8
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<InvincibleEnemy>(3, 0.8f)
		),
			EvectorforEmpty });
	//���̺� 9
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<SpinEnemy>(5, 0.5f)
		),
			EvectorforEmpty });

	//���̺� 10
	waves.push_back({ 10.f,
		SIvectorforEmpty,getEnemies<InvincibleEnemy>(5) });


#pragma endregion
}



void WaveManager::update()
{

	leftTime -= DELTATIME;
	if (leftTime <= 0)
	{
		//�����ϸ� �ð��� �����ٴ��� ���� ó�� �Ҹ��� ���ٴ��� 
		//�����츦 �� �޽����� �������� �ð��� �����ٴ°� ǥ���ϰ� ����
		if (wave >= 10)
			//���� ���̺�
		{
			waves.push_back({ 12.f,
				mergeSIVectors(
					getEnemiesInTime<BasicEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesInTime<SpinEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesInTime<DashEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesInTime<InvincibleEnemy>(randSpawnNum(), randSpawnTime()),
					
					getEnemiesTimeInterval<BasicEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesTimeInterval<SpinEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesTimeInterval<DashEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesTimeInterval<InvincibleEnemy>(randSpawnNum(), randSpawnTime())
				),
				mergeEVectors(
					getEnemies<BasicEnemy>(randSpawnNum()),
					getEnemies<SpinEnemy>(randSpawnNum()),
					getEnemies<DashEnemy>(randSpawnNum()),
					getEnemies<DashEnemy>(randSpawnNum())
				)
				});
		}
		if (waves.size() > 0)
		{
			++wave;
			leftTime = waves[wave].waveContinueTime;
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
}

void WaveManager::release()
{
}
