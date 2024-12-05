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

UpgradeComponent::UpgradeComponent()
{
}

UpgradeComponent::~UpgradeComponent()
{
}

void UpgradeComponent::initialize()
{
	DamageUpgrade* damageUpgrade = new DamageUpgrade(nullptr, L"CCTV.exe 강화", L"CCTV.exe가 더욱 강해집니다.");
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
	int index = utils::ExMath::getRandomValue(0, _upgrades.size());
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
						};
				};
			GET_SINGLETON(EventManager)->createObject(windowUI, LAYER::UI);
			GET_SINGLETON(Core)->OnMessageProcessEvent -= [this, upgrade]() {};
		};
	if (!upgrade->isValid())
	{
		auto iter = std::find(_upgrades.begin(), _upgrades.end(), upgrade);
		_upgrades.erase(iter);
		_finishedUpgrade.push_back(*iter);
	}
}