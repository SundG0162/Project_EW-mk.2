#include "pch.h"
#include "PanelUI.h"

PanelUI::PanelUI()
{
}

PanelUI::~PanelUI()
{
	for (auto& pair : _uiMap)
	{
		delete pair.second;
	}
}

void PanelUI::update()
{
	for (auto& pair : _uiMap)
	{
		if (pair.second->isDead())
		{
			auto iter = _uiMap.find(pair.first);
			delete& iter;
			_uiMap.erase(iter);
		}
		pair.second->update();
	}
}

void PanelUI::render(HDC hdc)
{
	for (auto& pair : _uiMap)
	{
		pair.second->render(hdc);
	}
}

void PanelUI::addUI(const wstring& key, UI* ui)
{
	if (_uiMap.find(key) != _uiMap.end())
		return;
	_uiMap.insert({ key, ui });
}

void PanelUI::removeUI(const wstring& key)
{
	auto iter = _uiMap.find(key);
	if (iter != _uiMap.end())
	{
		iter->second->setDead();
	}
}

void PanelUI::enableUI(const wstring& key)
{
	auto iter = _disabledUiMap.find(key);
	if (iter != _disabledUiMap.end())
	{
		_uiMap.insert(*iter);
		_disabledUiMap.erase(iter);
	}
}

void PanelUI::disableUI(const wstring& key)
{
	auto iter = _uiMap.find(key);
	if (iter != _uiMap.end())
	{
		_disabledUiMap.insert(*iter);
		_uiMap.erase(iter);
	}
}
