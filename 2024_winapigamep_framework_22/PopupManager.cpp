#include "pch.h"
#include "PopupManager.h"
#include "Core.h"
#include "WindowUI.h"
#include "UI.h"
#include "EventManager.h"
#include "Window.h"
#include "WindowUI.h"
#include "WindowManager.h"
#include "TextUI.h"
#include "ImageUI.h"

PopupManager::~PopupManager()
{
	for (auto pair : _uiMap)
	{
		SAFE_DELETE(pair.second);
	}
}

void PopupManager::initialize()
{
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
			WindowUI* ui = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { 300,70 }, WINDOW_TYPE::NEW, L"NotEnoughMoney");
			TextUI* text = new TextUI();
			text->setupFont(L"Galmuri9 Regular", 35, 400);
			text->setText(L"전력이 부족합니다.");
			text->setPosition({ 150, 25 });
			ui->setUI(text);
			
			ui->getWindow()->OnTryWindowCloseEvent += [ui]()
				{
					GET_SINGLETON(PopupManager)->close(L"NotEnoughPower", false);
				};
			addPopup(L"NotEnoughPower", ui);
			ui->getWindow()->closeWindow();
			GET_SINGLETON(EventManager)->excludeWindow(ui->getWindow());
			ui->getWindow()->OnWindowCloseEvent -= [ui]() {};
		};
}

void PopupManager::release()
{
	for (auto& pair : _uiMap)
	{
		GET_SINGLETON(EventManager)->deleteObject(pair.second);
	}
}

void PopupManager::addPopup(const wstring& key, WindowUI* ui)
{
	auto iter = _uiMap.find(key);
	if (iter != _uiMap.end())
		return;
	_uiMap.insert({ key, ui });
}

WindowUI* PopupManager::getPopup(const wstring& key)
{
	auto iter = _uiMap.find(key);
	if (iter != _uiMap.end())
		return iter->second;
	return nullptr;
}

void PopupManager::popup(const wstring& key, const Vector2& position, bool withTween)
{
	WindowUI* wndUI = getPopup(key);
	if (!wndUI->getWindow()->isClosed())
	{
		wndUI->getWindow()->openTween(0.f, 3.f);
		return;
	}
	wndUI->getWindow()->openWindow();
	wndUI->setPosition(position);
	wndUI->getWindow()->setCloseable(false);
	wndUI->getWindow()->setMoveable(true);
	GET_SINGLETON(EventManager)->createObject(wndUI, LAYER::UI);
	GET_SINGLETON(EventManager)->createWindow(wndUI->getWindow());
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
				GET_SINGLETON(EventManager)->excludeWindow(wndUI->getWindow());
				GET_SINGLETON(EventManager)->excludeObject(wndUI, LAYER::UI);
				wndUI->getWindow()->closeWindow();
			};
	}
	else
	{
		GET_SINGLETON(EventManager)->excludeWindow(wndUI->getWindow());
		GET_SINGLETON(EventManager)->excludeObject(wndUI, LAYER::UI);
		wndUI->getWindow()->closeWindow();
	}
}
