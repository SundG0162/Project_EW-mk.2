#pragma once
#include "SpawnManager.h"
#include "Enemy.h"
#include "Component.h"
#include "Stat.h"
#include "StatComponent.h"
#include <type_traits>

struct WaveInfo
{
	float waveContinueTime;
	vector<SpawnInfo> spawnList; //지연 가능함
	vector<Enemy> spawnEnemyList; //지연 할필요 없음.
};

class WaveManager
{
	DECLARE_SINGLETON(WaveManager);
public:
	void init();
	void update();


public:
	template <typename T>
	void CreateAllocatedEnemy()//wave에 따른 스탯 증가 처리용 함수
	{
		T enemy = new T;
		StatComponent statCompo = enemy.getComponent<StatComponent>();
		statCompo.getStat(L"")
	}

template <typename T>
	vector<Enemy> getAllocEnemies(int number)
	{
		vector<Enemy> result;
		for (int i = 0; i < number; i++)
		{
			{
				T enemy = new T;
				result.push_back(enemy);
			}
		}
		return result;
	}
	template <typename T>
	vector<SpawnInfo> getAllocatedEnemiesInTime(int number, float time)
	{
		vector<SpawnInfo> result;
		for (int i = 0; i < number; i++)
		{
			{
				T enemy = new T;
				result.push_back({ enemy, time });
			}
		}
		return result;
	}
	template <typename T>
	vector<SpawnInfo> getAllocatedEnemiesTimeInterval(int number, float time)
	{
		vector<SpawnInfo> result;
		for (int i = 0; i < number; i++)
		{
			{
				T enemy = new T;
				result.push_back({ enemy, time * i });
			}
		}
		return result;
	}
	// Base case for merging two vectors of the same type
	template <typename T>
	std::vector<T> mergeVectors(const std::vector<T>& A, const std::vector<T>& B) {
		std::vector<T> merged;
		merged.reserve(A.size() + B.size());
		merged.insert(merged.end(), A.begin(), A.end());
		merged.insert(merged.end(), B.begin(), B.end());
		return merged;
	}

	// Variadic template for merging multiple vectors
	template <typename T, typename... Rest>
	std::vector<T> mergeVectors(const std::vector<T>& first, const Rest&... rest) {
		return mergeVectors(first, mergeVectors(rest...));
	}
private:
	int wave = 0;
	float leftTime = 0.f;
	vector<WaveInfo> waves;
};