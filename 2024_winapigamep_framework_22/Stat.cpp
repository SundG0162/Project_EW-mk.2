#include "pch.h"
#include "Stat.h"

Stat::Stat(float baseValue)
{
	_modifiedValue = 0.f;
	_baseValue = baseValue;
}

Stat::~Stat()
{
}

void Stat::addModifier(void* key, float value)
{
	auto iter = _modifierMap.find(key);
	if (iter != _modifierMap.end()) //���� �̹� �����ϴ� Ű�� ����
	{
		_modifiedValue -= iter->second;
		iter->second = value;
	}
	else
	{
		_modifierMap.insert({ key, value });
	}
	_modifiedValue += value;
}

void Stat::removeModifier(void* key)
{
	auto iter = _modifierMap.find(key);
	if (iter != _modifierMap.end())
	{
		_modifiedValue -= iter->second;
		_modifierMap.erase(key);
	}
}
