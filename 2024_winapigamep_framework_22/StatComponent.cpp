#include "pch.h"
#include "StatComponent.h"

StatComponent::StatComponent()
{
}

StatComponent::~StatComponent()
{
	map<wstring, Stat*>::iterator iter;
	for (iter = _statMap.begin(); iter != _statMap.end(); ++iter)
	{
		delete iter->second;
	}
	_statMap.clear();
}

void StatComponent::lateUpdate()
{
}

void StatComponent::render(HDC hDC)
{
}

void StatComponent::addStat(const wstring& key, Stat* stat)
{
	if (_statMap.find(key) != _statMap.end()) // �̹� �����ϴ� Ű��� ��
		return;
	_statMap.insert({ key, stat });
}

Stat* StatComponent::getStat(const wstring& key)
{
	auto iter = _statMap.find(key);
	if (iter != _statMap.end())
	{
		return iter->second;
	}
	return nullptr;
}

