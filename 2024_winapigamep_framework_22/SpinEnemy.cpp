#include "pch.h"
#include "SpinEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"

SpinEnemy::SpinEnemy()
{
}

SpinEnemy::SpinEnemy(Object* target)
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	GET_SINGLETON(ResourceManager)->loadTexture(L"LongHead", L"Texture\\LongHead.bmp");
	sp->setSprite(utils::SpriteParser::textureToSprite(
		GET_SINGLETON(ResourceManager)->getTexture(L"LongHead")));
	Collider* collider = addComponent<Collider>();
	SetTarget(target);
	SetRandomPos();
	_moveSpeed = 300.f;
}

SpinEnemy::~SpinEnemy()
{
}

void SpinEnemy::update()
{
	Super::update();
	utils::ExMath::rotateVector(_moveVector, 90);
	_moveVector = _moveVector*1.8f;
	DoMove(_moveVector);
	_moveVector = _moveVector/1.8f;
}

void SpinEnemy::render(HDC hdc)
{
	Super::render(hdc);
}
