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

Camera::Camera(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"Camera.exe")
{
	_maxCount = 3;
	_counter = _maxCount;
	_window->OnWindowMoveEvent += [this](const Vector2& prev, const Vector2& current)
		{
			this->handleOnWindowMove(prev, current);
		};
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	Sprite* sprite = utils::SpriteParser::textureToSprite(GET_SINGLETON(ResourceManager)->findTexture(L"Camera"));
	renderer->setSprite(sprite);
	renderer->setScale({ 5, 5 });
	_window->setCloseable(false);
	_window->setMoveable(true);
	int sizeX = size.x * 0.8f;
	int sizeY = sizeX / 8;
	_bar = new BarUI({ position.x, position.y + size.y / 2 - sizeY }, { sizeX, sizeY });
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
	if (_timer > 1)
	{
		_timer = 0;
		_counter--;
		_bar->setFillAmount((float)_counter / _maxCount);
		if (_counter == 0)
		{
			GET_SINGLETON(EventManager)->deleteObject(this);
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
	int sizeX = _size.x * 0.8f;
	int sizeY = sizeX / 8;
	_bar->setPosition({ _position.x, _position.y + _size.y / 2 - sizeY });
}
