#pragma once
#include "SpawnManager.h"
#include "Enemy.h"
#include "Component.h"
#include "Stat.h"
#include "StatComponent.h"
#include <type_traits>
#include <math.h>

struct WaveInfo
{
	float waveContinueTime;
	vector<SpawnInfo> spawnList; //지연 가능함
	vector<Enemy*> spawnEnemyList; //지연 할필요 없음.
};

class WaveManager
{
	DECLARE_SINGLETON(WaveManager);
public:
	void init();
	void update();


public:
	int getHPIncByWave()
	{
		int inc = 0;
		inc += wave / 3;
		if (wave > 5) inc += 1;
		if (wave > 10) inc += 2;
		if (wave > 15) inc += 3;
		return inc;
	}

	int randSpawnNum()
	{
		int basenum = wave - 8;
		basenum = utils::ExMath::getRandomValue(basenum / 3, basenum/2);
		return basenum;
	}
	int randSpawnTime()
	{
		float basenum = wave - 8;
		basenum = utils::ExMath::getRandomValue(0.f, 1.f/basenum);
		return basenum;
	}

	template <typename T = Enemy>
	T* CreateAllocatedEnemy()//wave에 따른 스탯 증가 처리용 함수
	{
		T* enemy = new T;
		StatComponent* statCompo = enemy->getComponent<StatComponent>();
		statCompo->getStat(L"maxHealth")->addModifier(this, getHPIncByWave());
		statCompo->getStat(L"powerEarnOnDead", new Stat((int)pow(wave, 1.5f) + 10));
		return enemy;
	}

	template <typename T>
	vector<Enemy*> getEnemies(int number)
	{
		vector<Enemy*> result;
		for (int i = 0; i < number; i++)
		{
			{
				T* enemy = CreateAllocatedEnemy<T>();
				result.push_back(enemy);
			}
		}
		return result;
	}
	template <typename T>
	vector<SpawnInfo> getEnemiesInTime(int number, float time)
	{
		vector<SpawnInfo> result;
		for (int i = 0; i < number; i++)
		{
			{
				T* enemy = CreateAllocatedEnemy<T>();
				result.push_back({ enemy, time });
			}
		}
		return result;
	}
	template <typename T>
	vector<SpawnInfo> getEnemiesTimeInterval(int number, float time)
	{
		vector<SpawnInfo> result;
		for (int i = 0; i < number; i++)
		{
			{
				T* enemy = CreateAllocatedEnemy<T>();
				result.push_back({ enemy, time * i });
			}
		}
		return result;
	}

	std::vector<SpawnInfo> mergeSIVectors(const std::vector<SpawnInfo>& A, const std::vector<SpawnInfo>& B) {
		std::vector<SpawnInfo> merged;
		merged.reserve(A.size() + B.size());
		merged.insert(merged.end(), A.begin(), A.end());
		merged.insert(merged.end(), B.begin(), B.end());
		return merged;
	}


	template <typename... Rest>
	std::vector<SpawnInfo> mergeSIVectors(const std::vector<SpawnInfo>& first, const Rest&... rest) {
		return mergeSIVectors(first, mergeSIVectors(rest...));
	}

	std::vector<Enemy*> mergeEVectors(const std::vector<Enemy *>& A, const std::vector<Enemy*>& B) {
		std::vector<Enemy*> merged;
		merged.reserve(A.size() + B.size());
		merged.insert(merged.end(), A.begin(), A.end());
		merged.insert(merged.end(), B.begin(), B.end());
		return merged;
	}

	template <typename... Rest>
	std::vector<Enemy*> mergeEVectors(const std::vector< Enemy* >& first, const Rest&... rest) {
		return mergeEVectors(first, mergeEVectors(rest...));
	}

private:
	int wave = 0;
	float leftTime = 0.f;
	vector<WaveInfo> waves; //이거 큐로 바꿔줘야하는데 시간이 없어 ㅠㅠㅠ
	vector<SpawnInfo> SIvectorforEmpty;
	vector<Enemy*> EvectorforEmpty;
};