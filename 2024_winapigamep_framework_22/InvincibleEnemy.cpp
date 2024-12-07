#include "pch.h"
#include "InvincibleEnemy.h"
#include "ResourceManager.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Collider.h"

InvincibleEnemy::InvincibleEnemy()
{
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	renderer->setScale({ 2,2 });
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"EnemySheet");
	Animator* anim = getComponent<Animator>();

	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 2 }, { 32,32 }, 6);
		anim->createAnimation(L"invincibleEnd", vecsprite, 0.1f * 6);
	}
	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 2 }, { 32,32 }, 6);
		reverse(vecsprite.begin(), vecsprite.end());
		anim->createAnimation(L"invincibleStart", vecsprite, 0.1f * 6);
	}
	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 3 }, { 32,32 }, 2);
		anim->createAnimation(L"move", vecsprite, 0.2f * 2);
	}
	anim->playAnimation(L"move", true);
	anim->findAnimation(L"invincibleEnd")->OnAnimationEndEvent += [this]() 
		{
			getComponent<Animator>()->playAnimation(L"move", true);
			getComponent<Collider>()->setOffset({ 0,0 });
			stat->getStat(L"moveSpeed")->removeModifier(this);
		};

	anim->findAnimation(L"invincibleStart")->OnAnimationEndEvent += [this]()
		{
			getComponent<Collider>()->setOffset({ 5555,5555 });
		};
	

	stat->getStat(L"moveSpeed")->setValue(40.f);
	stat->getStat(L"CoolTime")->setValue(3.f);
	stat->getStat(L"SkilTime")->setValue(3.f);
}

InvincibleEnemy::~InvincibleEnemy()
{
}

void InvincibleEnemy::update()
{
	Super::update();
}

void InvincibleEnemy::render(HDC hdc)
{
	Super::render(hdc);
}

void InvincibleEnemy::startSkill()
{
	useSkill();
	
}

void InvincibleEnemy::updateSkill()
{
}

void InvincibleEnemy::endSkill()
{
	useSkill();
}

void InvincibleEnemy::useSkill()
{
	_isUsing = !_isUsing;
	if (_isUsing)
	{
		getComponent<Animator>()->playAnimation(L"invincibleStart", false);
		stat->getStat(L"moveSpeed")->addModifier(this, -30);
	}
	else
	{
		getComponent<Animator>()->playAnimation(L"invincibleEnd", false);
	}
}
