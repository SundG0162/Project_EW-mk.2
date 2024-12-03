#include "pch.h"
#include "BasicEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"

BasicEnemy::BasicEnemy()
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	sp->setSprite(GET_SINGLETON(ResourceManager)->getSprite(L"BasicEnemy"));
	Collider* collider = addComponent<Collider>();
	cout << "setted";
	//collider->enterCollision
}

BasicEnemy::BasicEnemy(Object* target)
{
	//SetTarget(target);
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	sp->setSprite(GET_SINGLETON(ResourceManager)->getSprite(L"BasicEnemy"));
	Collider* collider = addComponent<Collider>();
	SetTarget(target);
	SetRandomPos();
}

BasicEnemy::~BasicEnemy()
{
}

void BasicEnemy::update()
{
	Enemy::update();
}

void BasicEnemy::render(HDC hdc)
{
	Enemy::render(hdc);
}
