#include "pch.h"
#include "Camera.h"
#include "TimeManager.h"
#include "GDISelector.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "BarUI.h"
#include "FadeInOut.h"

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
}

Camera::~Camera()
{
	_window->OnWindowMoveEvent -= [this](const Vector2& prev, const Vector2& current)
		{
			this->handleOnWindowMove(prev, current);
		};
}

void Camera::update()
{
	_timer += DELTATIME;
	if (_fadeOut && !_window->isTweening())
	{
		if (_timer > 0.7f)
		{
			_window->closeTween(0);
			_window->OnTweenEndEvent += [this]() 
				{
					GET_SINGLETON(EventManager)->deleteObject(this);
				};
		}
		return;
	}
	if (_timer > 1)
	{
		_timer = 0;
		_counter--;
		_bar->setFillAmount((float)_counter / _maxCount);
		if (_counter == 0)
		{
			_fadeOut = new FadeInOut(_position, _size);
			_fadeOut->init(0.8f, FADE_TYPE::FADE_OUT);
			_window->setMoveable(false);
			getComponent<SpriteRenderer>()->setSprite(nullptr);
			GET_SINGLETON(SceneManager)->getCurrentScene()->addObject(_fadeOut, LAYER::EFFECT);
			return;
		}
	}
}

void Camera::render(HDC hdc)
{
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
