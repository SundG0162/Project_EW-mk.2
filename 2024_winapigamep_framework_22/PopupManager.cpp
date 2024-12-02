#include "pch.h"
#include "PopupManager.h"
#include "WindowUI.h"
#include "UI.h"
#include "EventManager.h"
#include "Window.h"

PopupManager::~PopupManager()
{
	for (auto pair : _uiMap)
	{
		SAFE_DELETE(pair.second);
	}
}

void PopupManager::addPopup(const wstring& key, UI* ui, const wstring& name)
{
	WindowUI* wndUI = getPopup(key);
	if (wndUI)
		return;
	wndUI = new WindowUI(ui->getPosition(), ui->getSize(), WINDOW_TYPE::NEW, name);
	wndUI->setUI(ui);
	_uiMap.insert({ key, wndUI });
}

WindowUI* PopupManager::getPopup(const wstring& key)
{
	auto iter = _uiMap.find(key);
	if (iter != _uiMap.end())
		return iter->second;
	return nullptr;
}

void PopupManager::popUp(const wstring& key, const Vector2& position, bool withTween)
{
	WindowUI* wndUI = getPopup(key);
	wndUI->setPosition(position);
	wndUI->getWindow()->setSize(wndUI->getSize());
	GET_SINGLETON(EventManager)->createObject(wndUI, LAYER::UI);
	if (withTween)
		wndUI->getWindow()->openTween(0.f);
}

void PopupManager::close(const wstring& key, bool withTween)
{
	WindowUI* wndUI = getPopup(key);
	if (withTween)
	{
		wndUI->getWindow()->closeTween(0.f);
		wndUI->getWindow()->OnTweenEndEvent += [this, wndUI]()
			{
				GET_SINGLETON(EventManager)->excludeObject(wndUI, LAYER::UI);
			};
	}
	else
	{
		GET_SINGLETON(EventManager)->excludeObject(wndUI, LAYER::UI);
	}
}
