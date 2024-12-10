#include "pch.h"
#include "Effect.h"
#include "Animator.h"
#include "AnimationClip.h"
#include "EventManager.h"

Effect::Effect()
{
	_animator = addComponent<Animator>();
}

Effect::~Effect()
{
}

void Effect::update()
{
	componentUpdate();
}

void Effect::render(HDC hdc)
{
	componentRender(hdc);
}

void Effect::setClip(AnimationClip* clip)
{
	_animator->addAnimation(L"Effect", clip);
}

void Effect::play(bool isRepeat)
{
	_animator->playAnimation(L"Effect", isRepeat);
	if (!isRepeat)
	{
		_animator->findAnimation(L"Effect")->OnAnimationEndEvent += 
			[this]()
			{
				GET_SINGLETON(EventManager)->deleteObject(this);
			};
	}
}

void Effect::stop()
{
	//todo : 구현하기
}

