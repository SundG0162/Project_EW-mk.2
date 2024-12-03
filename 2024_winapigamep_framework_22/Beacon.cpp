#include "pch.h"
#include "Beacon.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "BarUI.h"
#include "Window.h"
#include "WindowUI.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Animator.h"
#include "SpriteRenderer.h"

Beacon::Beacon(const Vector2& position, const Vector2& size) : CaptureObject(position, size, WINDOW_TYPE::COPY, L"Beacon.exe")
{
	_duration = 10.f;
	_timer = 0.f;
	_settingUp = false;
	_bar = new WindowUI({ position.x - 30, position.y - size.y / 3 }, { 320,40 }, WINDOW_TYPE::NEW, L"Ember.exe");
	BarUI* bar = new BarUI({ _bar->getSize().x / 2, _bar->getSize().y / 2 }, { 320,40 });
	_bar->getWindow()->setMoveable(true);
	_bar->getWindow()->setCloseable(true);
	_bar->setUI(bar);
	GET_SINGLETON(EventManager)->createObject(_bar, LAYER::UI);
	Texture* texture = GET_SINGLETON(ResourceManager)->getTexture(L"Torch");
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	RECT rect = { 0,0,_size.x,_size.y };
	GetWindowRect(_window->getHWnd(), &rect);
	Vector2 offset = utils::CoordinateSync::nonClientToClient(rect, _position) - _position;
	renderer->setScale({ 5,5 });
	renderer->setOffset(offset);
	Animator* animator = addComponent<Animator>();
	vector<Sprite*> sprites = utils::SpriteParser::textureToSprites(texture, { 0,0 }, { 32,32 }, { 32,0 });
	animator->createAnimation(L"Idle", sprites, 0.5f);
	animator->playAnimation(L"Idle", true);
}

Beacon::~Beacon()
{
}

void Beacon::update()
{
	_timer += DELTATIME;
	if (_settingUp)
	{
		_position.x = std::lerp(_startPos.x, _goalPos.x, utils::Ease::outCubic(_timer));
		_position.y = std::lerp(_startPos.y, _goalPos.y, utils::Ease::outCubic(_timer));
		_window->moveWindow(_position);
		if (_timer > 1)
		{
			_timer = 0.f;
			_settingUp = false;
		}
	}
	float ratio = 1 - _timer / _duration;
	dynamic_cast<BarUI*>(_bar->getUI())->setFillAmount(ratio);
	if (_timer >= _duration && !_window->isTweening())
	{
		_window->closeTween(0.5f);
		_bar->getWindow()->closeTween(0);
		_window->OnTweenEndEvent += [this]()
			{
				GET_SINGLETON(EventManager)->deleteObject(this);
				delete _bar;
			};
	}
}

void Beacon::render(HDC hdc)
{
	componentRender(hdc);
}

void Beacon::setup(const Vector2& position)
{
	_goalPos = position;
	_startPos = _position;
	_settingUp = true;
}
