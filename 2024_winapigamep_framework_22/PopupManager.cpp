#include "pch.h"
#include "PopupManager.h"
#include "Core.h"
#include "WindowUI.h"
#include "UI.h"
#include "EventManager.h"
#include "Window.h"
#include "WindowUI.h"
#include "TimeManager.h"
#include "PanelUI.h"
#include "WindowManager.h"
#include "TextUI.h"
#include "ImageUI.h"

PopupManager::~PopupManager()
{
	release();
}

void PopupManager::initialize()
{
#pragma region NotEnoughPower
	{
		WindowUI* ui = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { 330,70 }, WINDOW_TYPE::NEW, L"Error.exe");
		TextUI* text = new TextUI();
		text->setupFont(35);
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
	}
#pragma endregion
#pragma region Pause
	{
		Vector2 panelPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		Vector2 panelSize = { 500,300 };
		WindowUI* ui = new WindowUI(panelPosition, panelSize, WINDOW_TYPE::NEW, L"Pause.exe");
		PanelUI* panel = new PanelUI();
		panel->setPosition(panelPosition);
		panel->setSize(panelSize);
		TextUI* text = new TextUI();
		text->setupFont(70);
		text->setText(L"일시정지.");
		text->setPosition({ panelSize.x / 2, panelSize.y / 2 - 35 });
		panel->addUI(L"TitleText", text);
		ui->setUI(panel);
		ui->getWindow()->OnWindowOpenEvent += [ui]()
			{
				cout << "엣";
				GET_SINGLETON(TimeManager)->setTimeScale(0.f);
			};
		ui->getWindow()->OnTryWindowCloseEvent += [ui]()
			{
				GET_SINGLETON(TimeManager)->setTimeScale(1.f);
				GET_SINGLETON(PopupManager)->close(L"Pause", false);
			};
		addPopup(L"Pause", ui);
		ui->getWindow()->closeWindow();
		GET_SINGLETON(EventManager)->excludeWindow(ui->getWindow());
		ui->getWindow()->OnWindowCloseEvent -= [ui]() {};
	}
#pragma endregion
}

void PopupManager::release()
{
	for (auto& pair : _uiMap)
	{
		delete pair.second;
	}
	_uiMap.clear();
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

void PopupManager::popup(const wstring& key, const Vector2& position, bool withTween, float speed)
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
		wndUI->getWindow()->openTween(0.f, speed);
}

void PopupManager::close(const wstring& key, bool withTween, float speed)
{
	WindowUI* wndUI = getPopup(key);
	if (withTween)
	{
		wndUI->getWindow()->closeTween(0.f, speed);
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
