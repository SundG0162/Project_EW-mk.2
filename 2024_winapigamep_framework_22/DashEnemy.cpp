#include "pch.h"
#include "DashEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "StatComponent.h"
#include "Stat.h"


DashEnemy::DashEnemy(Object* target)
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	GET_SINGLETON(ResourceManager)->loadTexture(L"LongHead", L"Texture\\LongHead.bmp");
	sp->setSprite(utils::SpriteParser::textureToSprite(
		GET_SINGLETON(ResourceManager)->getTexture(L"LongHead")));

	Collider* collider = addComponent<Collider>();
	SetTarget(target);
	SetRandomPos();
	_moveSpeed = 20.f;
	sc = addComponent<StatComponent>();
	sc->addStat(L"DashRatio", new Stat(0.3f));

	SetSkillCoolTime(2.f);
	SetSkillUseTime(0.1f);
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
	Vector2 dashLength = toTarget * sc->getStat(L"DashRatio")->getValue();;

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
