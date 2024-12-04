#include "pch.h"
#include "SkillEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"

SkillEnemy::SkillEnemy()
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	GET_SINGLETON(ResourceManager)->loadTexture(L"LongHead", L"Texture\\LongHead.bmp");
	sp->setSprite(utils::SpriteParser::textureToSprite(
		GET_SINGLETON(ResourceManager)->getTexture(L"LongHead")));
	Collider* collider = addComponent<Collider>();
	cout << "setted";
	//collider->enterCollision
}

SkillEnemy::SkillEnemy(Object* target)
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

SkillEnemy::~SkillEnemy()
{
}

void SkillEnemy::update()
{
	if (_skilluseTime > 0)
	{
		_skilluseTime -= DELTATIME;
		updateSkill();
	}
	else
	{
		_currentTime += DELTATIME;
		if (_currentTime > _skillcoolTime)
		{
			_currentTime = 0.f;
			_skilluseTime = _skillTime;
			startSkill();
			_isUsingSkillOver = true;
		}
		else if (_isUsingSkillOver)
		{
			endSkill();
			_isUsingSkillOver = false;
		}
	}
	Enemy::update();

}

void SkillEnemy::render(HDC hdc)
{
	Enemy::render(hdc);
}

void SkillEnemy::useSkill()
{
}

void SkillEnemy::startSkill()
{
}

void SkillEnemy::updateSkill()
{
}

void SkillEnemy::endSkill()
{
}

