#include "pch.h"
#include "DashEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "StatComponent.h"
#include "Stat.h"


DashEnemy::DashEnemy(Object* target):Super(target)
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	sp->setSprite(GET_SINGLETON(ResourceManager)->getSprite(L"BasicEnemy"));

	stat->addStat(L"DashRatio", new Stat(0.3f));

	stat->getStat(L"moveSpeed")->setValue(20.f);
	stat->getStat(L"CoolTime")->setValue(5.f);
	stat->getStat(L"SkilTime")->setValue(0.1f);
}

DashEnemy::~DashEnemy()
{
}

void DashEnemy::update()
{
	Super::update();
}

void DashEnemy::render(HDC hdc)
{
	Super::render(hdc);
}

void DashEnemy::startSkill()
{
	if (toTarget.Length() < 50) return;
	Vector2 dashLength = toTarget * stat->getStat(L"DashRatio")->getValue();

	DoMove(dashLength);
	cout << "startdash" << std::endl;
}

void DashEnemy::updateSkill()
{
	//cout << "updatedash" << std::endl;
}

void DashEnemy::endSkill()
{
	cout << "enddash" << std::endl;
}
