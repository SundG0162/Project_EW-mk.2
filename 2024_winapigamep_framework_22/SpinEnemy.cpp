#include "pch.h"
#include "SpinEnemy.h"
#include "SpriteRenderer.h"
#include "StatComponent.h"
#include "Stat.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Stat.h"
#include "StatComponent.h"

SpinEnemy::SpinEnemy()
{
	stat->addStat(L"SpinRatio", new Stat(1.5f));

	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	sp->setSprite(GET_SINGLETON(ResourceManager)->getSprite(L"BasicEnemy"));

	stat->getStat(L"moveSpeed")->setValue(150.f);
}

SpinEnemy::~SpinEnemy()
{
}

void SpinEnemy::update()
{
	Super::update();
	if (toTarget.Length() < 50) return;
	utils::ExMath::rotateVector(_moveVector, 90);
	_moveVector = _moveVector * getComponent<StatComponent>()->getStat(L"SpinRatio")->getValue();
	DoMove(_moveVector);
	_moveVector = _moveVector / getComponent<StatComponent>()->getStat(L"SpinRatio")->getValue();
}

void SpinEnemy::render(HDC hdc)
{
	Super::render(hdc);
}
