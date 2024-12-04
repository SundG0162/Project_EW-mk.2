#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "CCTV.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SpriteRenderer.h"
#include "StatComponent.h"
#include "Stat.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Scene.h"
#include "Sprite.h"
#include "Beacon.h"
#include "Camera.h"
#include "Core.h"
#include "PlayerManager.h"

Player::Player(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"Me.exe")
{
	_window->setCloseable(false);
	_cctv = nullptr;
	_isBeaconSettingUp = false;
	_window->setPriority(PLAYER_PRIORITY);
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(L"Computer");
	spriteRenderer->setSprite(sprite);
	spriteRenderer->setScale({ 3,3 });
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
	Stat* beaconSizeStat = new Stat(300);
	_statComponent->addStat(L"BeaconSize", beaconSizeStat);
	GET_SINGLETON(PlayerManager)->setPlayer(this);
}

Player::~Player()
{
}


void Player::update()
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
	if (_isBeaconSettingUp && GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		Vector2 mousePos = Vector2(GET_MOUSEPOS);
		float size = _statComponent->getStat(L"BeaconSize")->getValue();
		GET_SINGLETON(Core)->OnMessageProcessEvent += [this, mousePos, size]()
			{
				_isBeaconSettingUp = false;
				Beacon* beacon = new Beacon(_position, { size,size });
				beacon->initialize(this);
				beacon->setup(mousePos);
				GET_SINGLETON(EventManager)->createObject(beacon, LAYER::UI);
			};
	}
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		float size = _statComponent->getStat(L"CameraSize")->getValue();
		GET_SINGLETON(Core)->OnMessageProcessEvent += [this, size]()
			{
				Camera* camera = new Camera(_position, { size,size });
				camera->initialize(this);
				GET_SINGLETON(EventManager)->createObject(camera, LAYER::UI);
			};
	}
	if (GET_KEYDOWN(KEY_TYPE::Q))
	{
		_statComponent->getStat(L"CameraCount")->addModifier(this, -1);
		_isBeaconSettingUp = !_isBeaconSettingUp;
	}
}

void Player::render(HDC hdc)
{
	componentRender(hdc);
}
