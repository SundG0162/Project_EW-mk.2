#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "CCTV.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SpriteRenderer.h"
#include "StatComponent.h"
#include "Stat.h"
#include "UpgradeComponent.h"
#include "UpgradeUI.h"
#include "WindowUI.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "PowerManager.h"
#include "PopupManager.h"
#include "Scene.h"
#include "Sprite.h"
#include "Torch.h"
#include "Camera.h"
#include "Core.h"
#include "Collider.h"
#include "PlayerManager.h"

Player::Player(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"Me.exe")
{
	_window->setCloseable(false);
	_cctv = nullptr;
	_maxHP = 3;
	_hp = _maxHP;
	_window->setPriority(PLAYER_PRIORITY);
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(L"Computer");
	spriteRenderer->setSprite(sprite);
	spriteRenderer->setScale({ 3,3 });
	Collider* collider = addComponent<Collider>();
	collider->setSize({ 85,85 });
	_statComponent = addComponent<StatComponent>();
	Stat* damageStat = new Stat(1);
	_statComponent->addStat(L"Damage", damageStat);
	Stat* sizeStat = new Stat(500);
	_statComponent->addStat(L"Size", sizeStat);
	Stat* attackSpeedStat = new Stat(1.5f);
	_statComponent->addStat(L"AttackSpeed", attackSpeedStat);
	Stat* attackStunStat = new Stat(0.f);
	_statComponent->addStat(L"AttackStun", attackStunStat);
	Stat* cameraStunStat = new Stat(1.5f);
	_statComponent->addStat(L"CameraStun", cameraStunStat);
	Stat* cameraDamageStat = new Stat(3);
	_statComponent->addStat(L"CameraDamage", cameraDamageStat);
	Stat* cameraSizeStat = new Stat(500);
	_statComponent->addStat(L"CameraSize", cameraSizeStat);
	Stat* cameraCountStat = new Stat(3);
	_statComponent->addStat(L"CameraCount", cameraCountStat);
	Stat* torchSizeStat = new Stat(300);
	_statComponent->addStat(L"TorchSize", torchSizeStat);
	GET_SINGLETON(PlayerManager)->setPlayer(this);
	_cctv = new CCTV(_position + Vector2(400, 0), { 500,500 });
	_cctv->initialize(this);
	GET_SINGLETON(EventManager)->createObject(_cctv, LAYER::UI);
	_upgradeComponent = addComponent<UpgradeComponent>();
	_upgradeComponent->initialize();
	_priceMap.insert({ PLAYER_ITEM::CAMERA, 50 });
	_priceMap.insert({ PLAYER_ITEM::TORCH, 40 });
	_priceMap.insert({ PLAYER_ITEM::UPGRADE, 70 });
	_currentItem = PLAYER_ITEM::CAMERA;
}

Player::~Player()
{
	delete _cctv;
}


void Player::update()
{
	if (!_isCCTVLocked)
	{
		Vector2 movement = {};
		if (GET_KEY(KEY_TYPE::W))
			movement.y -= 1;
		if (GET_KEY(KEY_TYPE::A))
			movement.x -= 1;
		if (GET_KEY(KEY_TYPE::S))
			movement.y += 1;
		if (GET_KEY(KEY_TYPE::D))
			movement.x += 1;
		movement.Normalize();
		movement *= 300 * DELTATIME;
		_cctv->localMove(movement);
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_1))
	{
		_currentItem = PLAYER_ITEM::CAMERA;
		OnItemChangeEvent.invoke(_currentItem);
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_2))
	{
		_currentItem = PLAYER_ITEM::TORCH;
		OnItemChangeEvent.invoke(_currentItem);
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_3))
	{
		_currentItem = PLAYER_ITEM::UPGRADE;
		OnItemChangeEvent.invoke(_currentItem);
	}
	if (GET_KEYDOWN(KEY_TYPE::SPACE) || GET_KEYDOWN(KEY_TYPE::ENTER))
	{
		if (!GET_SINGLETON(PowerManager)->trySpendPower(_priceMap[_currentItem]))
		{
			GET_SINGLETON(PopupManager)->popup(L"NotEnoughPower", { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, false);
			return;
		}
		switch (_currentItem)
		{
		case PLAYER_ITEM::CAMERA:
		{
			float size = _statComponent->getStat(L"CameraSize")->getValue();
			GET_SINGLETON(Core)->OnMessageProcessEvent += [this, size]()
				{
					Camera* camera = new Camera(_position, { size,size });
					camera->initialize(this);
					GET_SINGLETON(EventManager)->createObject(camera, LAYER::UI);
					GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
				};
			_priceMap[_currentItem] += 20;
		}
		break;
		case PLAYER_ITEM::TORCH:
		{
			Vector2 mousePos = Vector2(GET_MOUSEPOS);
			float size = _statComponent->getStat(L"TorchSize")->getValue();
			GET_SINGLETON(Core)->OnMessageProcessEvent += [this, mousePos, size]()
				{
					Torch* torch = new Torch(_position, { size,size });
					torch->initialize(this);
					torch->setup(mousePos);
					GET_SINGLETON(EventManager)->createObject(torch, LAYER::UI);
					GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
				};
			_priceMap[_currentItem] += 20;
		}
		break;
		case PLAYER_ITEM::UPGRADE:
		{
			_upgradeComponent->setRandomUpgrade();
			_priceMap[_currentItem] += 40;
		}
		}
		OnItemUseEvent.invoke(_currentItem, _priceMap[_currentItem]);
	}
	if (GET_KEYDOWN(KEY_TYPE::K))
	{
		GET_SINGLETON(PopupManager)->popup(L"PowerGenerator", _position, false);
		//GET_SINGLETON(PowerManager)->modifyPower(100);
	}
}

void Player::render(HDC hdc)
{
	componentRender(hdc);
}

void Player::modifyHP(int value)
{
	int prev = _hp;
	_hp += value;
	OnHPChangeEvent.invoke(prev, _hp);
}
