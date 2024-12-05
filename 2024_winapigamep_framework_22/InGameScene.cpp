#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "WindowUI.h"
#include "Window.h"
#include "BasicEnemy.h"
#include "SpinEnemy.h"
#include "DashEnemy.h"
#include "InvincibleEnemy.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "EventManager.h"
#include "PowerManager.h"
#include "TextUI.h"
#include "ImageUI.h"
#include "PanelUI.h"
#include "UpgradeUI.h"
#include "ResourceManager.h"
#include "PopupManager.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::init()
{
	Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Player* player = new Player(position, { 400,300 });
	PanelUI* panel = new PanelUI();
	Vector2 panelSize = { 200, 50 };
	Vector2 panelPosition = { SCREEN_WIDTH - panelSize.x / 2, panelSize.y / 2 + 20 };
	panel->setSize(panelSize);
	panel->setPosition({ panelSize.x / 2, panelSize.y / 2 });
	TextUI* powerText = new TextUI();
	powerText->setPosition({ panelSize.x / 2 + 16,panelSize.y / 4 });
	powerText->setupFont(L"Galmuri9 Regular", 25, 400);
	powerText->setText(L"0");
	Sprite* icon = GET_SINGLETON(ResourceManager)->getSprite(L"PowerIcon");
	ImageUI* powerIcon = new ImageUI(icon);
	powerIcon->setPosition({ 32.f, panelSize.y / 2 });
	panel->addUI(L"PowerText", powerText);
	panel->addUI(L"PowerIcon", powerIcon);
	_powerPanel = new WindowUI(panelPosition, panelSize, WINDOW_TYPE::NEW, L"Power.exe");
	_powerPanel->setUI(panel);
	_powerPanel->getWindow()->setMoveable(true);
	_powerPanel->getWindow()->setCloseable(false);
	_powerPanel->getWindow()->OnWindowMoveEvent += [this](const Vector2& prev, const Vector2& current)
		{
			_powerPanel->getWindow()->moveWindow(current);
			PanelUI* panel = _powerPanel->getUI<PanelUI>();
			panel->setPosition(current);
		};
	GET_SINGLETON(PowerManager)->OnPowerChangeEvent += [this](int prev, int current)
		{
			wstring value = std::format(L"{0}", current);
			_powerPanel->getUI<PanelUI>()->getUI<TextUI>(L"PowerText")->setText(value);
		};
	addObject(_powerPanel, LAYER::UI);
	addObject(player, LAYER::PLAYER);

#pragma region enemyspawn

	{
		SpinEnemy* basicEnemy = new SpinEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 0 });
	}
	{
		InvincibleEnemy* basicEnemy = new InvincibleEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 0 });
	}
	{
		BasicEnemy* basicEnemy = new BasicEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 0 });
	}
	{
		DashEnemy* basicEnemy = new DashEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 0 });
	}
	{
		SpinEnemy* basicEnemy = new SpinEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.f });
	}
	{
		InvincibleEnemy* basicEnemy = new InvincibleEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.1f });
	}
	{
		BasicEnemy* basicEnemy = new BasicEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.2f });
	}
	{
		DashEnemy* basicEnemy = new DashEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.3f });
	}
#pragma endregion
}

void InGameScene::update()
{
	Scene::update();
	if (GET_KEYDOWN(KEY_TYPE::K))
	{
		GET_SINGLETON(PopupManager)->popup(L"NotEnoughPower", { SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 200 }, false);
	}
	if (GET_KEYDOWN(KEY_TYPE::B))
	{
		GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
	}
}
