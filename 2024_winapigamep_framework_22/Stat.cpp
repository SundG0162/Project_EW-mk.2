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
	float prevValue = getValue();
	_modifiedValue += value;
	OnValueChangeEvent.invoke(prevValue, getValue());
}

void Stat::removeModifier(void* key)
{
	auto iter = _modifierMap.find(key);
	if (iter != _modifierMap.end())
	{
		float prevValue = getValue();
		_modifiedValue -= iter->second;
		OnValueChangeEvent.invoke(prevValue, getValue());
		_modifierMap.erase(key);
	}
}
