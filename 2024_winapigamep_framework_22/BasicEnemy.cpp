#include "pch.h"
#include "BasicEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "StatComponent.h"
#include "Stat.h"

BasicEnemy::BasicEnemy()
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	sp->setSprite(GET_SINGLETON(ResourceManager)->getSprite(L"BasicEnemy"));
	Collider* collider = addComponent<Collider>();
	cout << "setted";
	//collider->enterCollision
}

BasicEnemy::BasicEnemy(Object* target):Super(target)
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	sp->setSprite(GET_SINGLETON(ResourceManager)->getSprite(L"BasicEnemy"));
	getComponent<StatComponent>()->getStat(L"moveSpeed")->setValue(50.f);
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