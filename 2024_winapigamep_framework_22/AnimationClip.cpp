#include "pch.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "Sprite.h"
#include "Object.h"
#include "TimeManager.h"

AnimationClip::AnimationClip()
	: _animator(nullptr)
	, _currentFrame(0)
	, _duration(0.f)
	, _timer(0.f)
{
	//OnAnimationEnd = Action<int, int, int>();
}

AnimationClip::~AnimationClip()
{
}

void AnimationClip::update()
{
	if (_currentFrame >= _sprites.size() - 1)
	{
		return;
	}
	_timer += DELTATIME;
	if (_timer >= _duration)
	{
		_timer = 0.f;
		_currentFrame++;
		//OnAnimationEnd.Invoke(1, 2, 3);
	}
}

void AnimationClip::render(HDC hdc)
{
	Object* owner = _animator->getOwner();
	Sprite* sprite = _sprites[_currentFrame];
	Vector2 pos = owner->getPosition();
	Vector2 size = sprite->getSize();
	TransparentBlt(hdc, pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y, sprite->getSpriteDC(), 0, 0, size.x, size.y, sprite->getTransparent());
}

void AnimationClip::release()
{
	for (Sprite* sprite : _sprites)
	{
		SAFE_DELETE(sprite);
	}
	_sprites.clear();
}

void AnimationClip::create(vector<Sprite*>& sprites, float duration)
{
	_sprites = sprites;
	_duration = duration;
}