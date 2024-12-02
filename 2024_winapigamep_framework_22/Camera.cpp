#include "pch.h"
#include "Camera.h"
#include "TimeManager.h"
#include "GDISelector.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "BarUI.h"
#include "FadeInOut.h"
#include "Collider.h"
#include "Enemy.h"

Camera::Camera(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"Camera.exe")
{
	_maxCount = 3;
	_counter = _maxCount;
	_window->OnWindowMoveEvent += [this](const Vector2& prev, const Vector2& current)
		{
			this->handleOnWindowMove(prev, current);
		};
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(L"Camera");
	renderer->setSprite(sprite);
	renderer->setScale({ 5, 5 });
	_window->setCloseable(false);
	_window->setMoveable(true);
	int sizeX = size.x * 0.8f;
	int sizeY = sizeX / 8;
	//이 아래 코드는 쓸데없이 연산을 늘리는게 아니라 윈도우 밑면과의 여백을 주기위해 굳이 이렇게 연산하는 것입니다.
	_bar = new BarUI({ position.x, position.y + size.y / 2 - size.x / 8 }, { sizeX, sizeY });
	_fadeOut = nullptr;

	Collider* collider = addComponent<Collider>();
	collider->setSize(size);
	collider->OnCollisionEnterEvent += [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionExitEvent += [this](Collider* other) {this->handleOnCollisionExit(other); };
	collider->setFollowing(false);
}

Camera::~Camera()
{
	_window->OnWindowMoveEvent -= [this](const Vector2& prev, const Vector2& current)
		{
			this->handleOnWindowMove(prev, current);
		};
	Collider* collider = getComponent<Collider>();
	collider->OnCollisionEnterEvent -= [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionExitEvent -= [this](Collider* other) {this->handleOnCollisionExit(other); };
}

void Camera::update()
{
	Collider* collider = getComponent<Collider>();
	RECT rect = { 0,0,_size.x,_size.y };
	GetWindowRect(_window->getHWnd(), &rect);
	collider->setPosition(utils::CoordinateSync::nonClientToClient(rect, _position));
	_timer += DELTATIME;
	if (_fadeOut && !_window->isTweening())
	{
		if (_timer > 0.7f)
		{
			GET_SINGLETON(EventManager)->deleteObject(_bar);
			_bar = nullptr;
			_window->closeTween(0);
			_window->OnTweenEndEvent += [this]()
				{
					_window->setCloseable(true);
					GET_SINGLETON(EventManager)->deleteObject(_fadeOut);
					GET_SINGLETON(EventManager)->deleteObject(this);
				};
		}
		return;
	}
	if (_timer > 1)
	{
		_timer = 0;
		_counter--;
		if (_bar)
			_bar->setFillAmount((float)_counter / _maxCount);
		if (_counter == -1)
		{
			INPUT input = { 0 };
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &input, sizeof(INPUT));
			for (Enemy* enemy : _targets)
			{
				enemy->GetDamage(_attackDamage);
				enemy->GetStunned(1.2f);
			}
			_fadeOut = new FadeInOut(_position, _size);
			_fadeOut->init(0.8f, FADE_TYPE::FADE_OUT);
			_window->setMoveable(false);
			getComponent<SpriteRenderer>()->setSprite(nullptr);
			GET_SINGLETON(EventManager)->createObject(_fadeOut, LAYER::EFFECT);
			return;
		}
	}
}

void Camera::render(HDC hdc)
{
	if (_bar)
		_bar->render(hdc);
	componentRender(hdc);
}

void Camera::handleOnWindowMove(const Vector2& prev, const Vector2& current)
{
	_position = current;
	_window->moveWindow(_position);
	int sizeY = _size.x / 8;
	_bar->setPosition({ _position.x, _position.y + _size.y / 2 - sizeY });
}

void Camera::handleOnCollisionEnter(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
		_targets.push_back(enemy);
}

void Camera::handleOnCollisionExit(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
	{
		auto iter = std::find(_targets.begin(), _targets.end(), enemy);
		if (iter != _targets.end())
		{
			_targets.erase(iter);
		}
	}
}