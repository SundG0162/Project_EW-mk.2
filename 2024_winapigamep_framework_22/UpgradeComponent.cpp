#include "pch.h"
#include "UpgradeComponent.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "UpgradeUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "DamageUpgrade.h"
#include "SizeUpgrade.h"
#include "CCTVStunUpgrade.h"
#include "AttackSpeedUpgrade.h"
#include "CameraStunUpgrade.h"
#include "CameraDamageUpgrade.h"
#include "CameraCountUpgrade.h"
#include "CameraSizeUpgrade.h"
#include "TorchAttackSpeedUpgrade.h"
#include "TorchDamageUpgrade.h"
#include "TorchSizeUpgrade.h"
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
	{
		Upgrade* upgrade = new DamageUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe ������ ����", L"CCTV.exe�� ���� �������ϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new SizeUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe Ȯ��", L"CCTV.exe�� ���� �о����ϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CCTVStunUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe ��ȭ", L"CCTV.exe�� ������ ������\n���� ��� ����ϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new AttackSpeedUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe ���ݼӵ� ����", L"CCTV.exe�� ���� �����̰�\n�����մϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraStunUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe ��ȭ", L"Camera.exe�� ���� ���ߴ� �ð���\n������ϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraDamageUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe ������ ����", L"Camera.exe�� ���� �������ϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraCountUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe ��ȭ", L"Camera.exe�� ĸó �ӵ���\n�����մϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraSizeUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe Ȯ��", L"Camera.exe�� ���� �о����ϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new TorchAttackSpeedUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"TorchIcon"), L"Torch.exe ���ݼӵ� ����", L"Torch.exe�� ���� �����̰�\n�����մϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new TorchDamageUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"TorchIcon"), L"Torch.exe ������ ����", L"Torch.exe�� ���� �������ϴ�.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new TorchSizeUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"TorchIcon"), L"Torch.exe Ȯ��", L"Torch.exe�� ���� �о����ϴ�.");
		_upgrades.push_back(upgrade);
	}
	Player* player = dynamic_cast<Player*>(getOwner());
	for (Upgrade* u : _upgrades)
	{
		u->initialize(player);
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
	if (_upgradeFlag || _upgrades.empty()) return;
	int index = utils::ExMath::getRandomValue(0, _upgrades.size() - 1);
	Upgrade* upgrade = _upgrades[index];
	upgrade->applyUpgrade();
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this, upgrade]()
		{
			if (_upgradeFlag)
			{
				GET_SINGLETON(Core)->OnMessageProcessEvent -= [this, upgrade]() {};
				return;
			}
			_upgradeFlag = true;
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
			window->OnWindowCloseEvent += [this]()
				{
					_upgradeFlag = false;
				};
			GET_SINGLETON(EventManager)->createObject(windowUI, LAYER::UI);
		};
	if (!upgrade->isValid())
	{
		auto iter = std::find(_upgrades.begin(), _upgrades.end(), upgrade);
		_finishedUpgrade.push_back(*iter);
		_upgrades.erase(iter);
	}
}