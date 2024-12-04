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
	SetTarget(target);
	SetRandomPos();
}

BasicEnemy::~BasicEnemy()
{
}

void BasicEnemy::update()
{
	Super::update();
}

void BasicEnemy::render(HDC hdc)
{
	Super::render(hdc);
}
