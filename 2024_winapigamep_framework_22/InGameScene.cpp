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
#include "SpriteRenderer.h"
#include "PowerManager.h"
#include "TextUI.h"
#include "ImageUI.h"
#include "PanelUI.h"
#include "UpgradeUI.h"
#include "ResourceManager.h"
#include "PopupManager.h"
#include "PlayerManager.h"

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
	setupUI();
	addObject(player, LAYER::PLAYER);

#pragma region enemyspawn

	{
		InvincibleEnemy* basicEnemy = new InvincibleEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.1f });
	}
#pragma endregion
}

void InGameScene::update()
{
	Scene::update();
	if (GET_KEYDOWN(KEY_TYPE::K))
	{
		GET_SINGLETON(PopupManager)->popup(L"Pause", { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, true);
	}
	if (GET_KEYDOWN(KEY_TYPE::B))
	{
		GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
	}
}

void InGameScene::setupUI()
{
#pragma region PowerPanel
	{
		PanelUI* panelUI = new PanelUI();
		Vector2 panelSize = { 200, 50 };
		Vector2 panelPosition = { SCREEN_WIDTH - panelSize.x / 2, panelSize.y / 2 + 20 };
		panelUI->setSize(panelSize);
		panelUI->setPosition({ panelSize.x / 2, panelSize.y / 2 });
		TextUI* powerText = new TextUI();
		powerText->setPosition({ panelSize.x / 2 + 16,panelSize.y / 4 });
		powerText->setupFont(25);
		powerText->setText(L"0");
		Sprite* icon = GET_SINGLETON(ResourceManager)->getSprite(L"PowerIcon");
		ImageUI* powerIcon = new ImageUI(icon);
		powerIcon->setPosition({ 32.f, panelSize.y / 2 });
		panelUI->addUI(L"PowerText", powerText);
		panelUI->addUI(L"PowerIcon", powerIcon);
		_powerPanel = new WindowUI(panelPosition, panelSize, WINDOW_TYPE::NEW, L"Power.exe");
		_powerPanel->setUI(panelUI);
		_powerPanel->getWindow()->setMoveable(true);
		_powerPanel->getWindow()->setCloseable(false);
		GET_SINGLETON(PowerManager)->OnPowerChangeEvent += [this](int prev, int current)
			{
				wstring value = std::format(L"{0}", current);
				_powerPanel->getUI<PanelUI>()->getUI<TextUI>(L"PowerText")->setText(value);
			};
		addObject(_powerPanel, LAYER::UI);
	}
#pragma endregion
#pragma region HPUI
	{
		PanelUI* panelUI = new PanelUI();
		Vector2 panelSize = { 280,90 };
		Vector2 panelPosition = { panelSize.x / 2, panelSize.y / 2 + 20 };
		panelUI->setSize(panelSize);
		panelUI->setPosition({ panelSize.x / 2, panelSize.y / 2 });
		Sprite* heart = GET_SINGLETON(ResourceManager)->getSprite(L"Heart");
		int offset = 85;
		for (int i = 0; i < 3; i++)
		{
			int x = 50 + offset * i;
			ImageUI* image = new ImageUI(heart);
			image->getComponent<SpriteRenderer>()->setScale({ 2,2 });
			image->setPosition({ x, (int)panelSize.y / 2 });
			wstring key = std::format(L"{0}", i);
			panelUI->addUI(key.c_str(), image);
		}
		_hpUI = new WindowUI(panelPosition, panelSize, WINDOW_TYPE::NEW, L"HP.exe");
		_hpUI->setUI(panelUI);
		_hpUI->getWindow()->setMoveable(true);
		_hpUI->getWindow()->setCloseable(false);
		Player* player = GET_SINGLETON(PlayerManager)->getPlayer();
		player->OnHPChangeEvent += [this](int prev, int current)
			{
				if (prev > current)
				{
					wstring key = std::format(L"{0}", current);
					_hpUI->getUI<PanelUI>()->disableUI(key.c_str());
				}
				else
				{
					wstring key = std::format(L"{0}", current-1);
					_hpUI->getUI<PanelUI>()->enableUI(key.c_str());
				}
			};
		addObject(_hpUI, LAYER::UI);
	}
#pragma endregion
}
