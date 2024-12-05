#include "pch.h"
#include "UpgradeComponent.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "UpgradeUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "DamageUpgrade.h"
#include "EventManager.h"
#include "ResourceManager.h"

UpgradeComponent::UpgradeComponent()
{
	_upgradeFlag = false;
}

UpgradeComponent::~UpgradeComponent()
{
	for (Upgrade* upgrade : _upgrades)
	{
		delete upgrade;
		upgrade = nullptr;
	}
	_upgrades.clear();
	for (Upgrade* upgrade : _finishedUpgrade)
	{
		delete upgrade;
		upgrade = nullptr;
	}
	_finishedUpgrade.clear();
}

void UpgradeComponent::initialize()
{
	DamageUpgrade* damageUpgrade = new DamageUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe 강화", L"CCTV.exe가 더욱 강해집니다.");
	_upgrades.push_back(damageUpgrade);

	Player* player = dynamic_cast<Player*>(getOwner());
	for (Upgrade* upgrade : _upgrades)
	{
		upgrade->initialize(player);
	}
}

void UpgradeComponent::lateUpdate()
{
}

void UpgradeComponent::render(HDC hDC)
{
}

void UpgradeComponent::setRandomUpgrade()
{
	if (_upgradeFlag && _upgrades.empty()) return;
	_upgradeFlag = true;
	int index = utils::ExMath::getRandomValue(0, _upgrades.size() - 1);
	Upgrade* upgrade = _upgrades[index];
	upgrade->applyUpgrade();
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this, upgrade]()
		{
			UpgradeUI* upgradeUI = new UpgradeUI();
			upgradeUI->setUpgrade(upgrade);
			WindowUI* windowUI = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { 240,360 }, WINDOW_TYPE::NEW, L"Upgrade.exe");
			windowUI->setUI(upgradeUI);
			windowUI->openTween(0.f);
			Window* window = windowUI->getWindow();
			window->setCloseable(true);
			window->setMoveable(true);
			window->OnTweenEndEvent += [this, window, windowUI]()
				{
					window->closeTween(2.f);
					window->OnTweenEndEvent -= [this]() {};
					window->OnTweenEndEvent += [this, windowUI]()
						{
							GET_SINGLETON(EventManager)->deleteObject(windowUI);
							_upgradeFlag = false;
						};
				};
			GET_SINGLETON(EventManager)->createObject(windowUI, LAYER::UI);
			GET_SINGLETON(Core)->OnMessageProcessEvent -= [this, upgrade]() {};
		};
	if (!upgrade->isValid())
	{
		auto iter = std::find(_upgrades.begin(), _upgrades.end(), upgrade);
		_finishedUpgrade.push_back(*iter);
		_upgrades.erase(iter);
	}
}