#include "pch.h"
#include "BasicEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"

BasicEnemy::BasicEnemy()
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	GET_SINGLETON(ResourceManager)->loadTexture(L"LongHead", L"Texture\\LongHead.bmp");
	sp->setSprite(utils::SpriteParser::textureToSprite(
		GET_SINGLETON(ResourceManager)->getTexture(L"LongHead")));
	Collider* collider = addComponent<Collider>();
	cout << "setted";
	//collider->enterCollision
}

BasicEnemy::BasicEnemy(Object* target)
{
	//SetTarget(target);
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	GET_SINGLETON(ResourceManager)->loadTexture(L"LongHead", L"Texture\\LongHead.bmp");
	sp->setSprite(utils::SpriteParser::textureToSprite(
		GET_SINGLETON(ResourceManager)->getTexture(L"LongHead")));
	Collider* collider = addComponent<Collider>();
}

BasicEnemy::~BasicEnemy()
{
}

void BasicEnemy::init()
{
	Super::init();
	SetRandomPos();
}

void BasicEnemy::update()
{
	Enemy::update();
}

void BasicEnemy::render(HDC hdc)
{
	Enemy::render(hdc);
}
