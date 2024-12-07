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
	waves.push_back({ 8.f, SIvectorforEmpty, getAllocEnemies<BasicEnemy>(1) });

	//���̺� 2
	waves.push_back({ 10.f, SIvectorforEmpty, getAllocEnemies<BasicEnemy>(2) });

	//���̺� 3
	waves.push_back({ 12.f,
		mergeVectors(
			getAllocEnemies<DashEnemy>(1),
			getAllocEnemyInterval<BasicEnemy>(2, 1.5f)
		), 	EvectorforEmpty});


#pragma endregion

}



void WaveManager::update()
{
	leftTime -= DELTATIME;
	if (leftTime <= 0)
	{
		//�����ϸ� �ð��� �����ٴ��� ���� ó�� �Ҹ��� ���ٴ��� �����츦 �� �޽����� �������� �ð��� �����ٴ°� ǥ���ϰ� ����

		leftTime = waves[++wave];
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
