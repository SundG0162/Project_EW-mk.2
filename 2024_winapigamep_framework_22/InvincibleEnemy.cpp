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
}

InvincibleEnemy::InvincibleEnemy(Object* target) : Super(target)
{
	addComponent<SpriteRenderer>();
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"EnemySheet");
	Animator* anim = addComponent<Animator>();

	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 2 }, { 32,32 }, 6);
		anim->createAnimation(L"invincibleStart", vecsprite, 0.1f * 6);
	}
	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 2 }, { 32,32 }, 6);
		reverse(vecsprite.begin(), vecsprite.end());
		anim->createAnimation(L"invincibleEnd", vecsprite, 0.1f * 6);
	}
	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 3 }, { 32,32 }, 2);
		anim->createAnimation(L"move", vecsprite, 0.2f * 2);
	}
	anim->playAnimation(L"move", true);
	anim->findAnimation(L"invincibleEnd")->OnAnimationEndEvent += [this]() 
		{getComponent<Animator>()->playAnimation(L"move", true); };

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
	getComponent<Collider>()->setOffset({5555,5555});
	getComponent<Animator>()->playAnimation(L"invincibleStart", false);
	stat->getStat(L"moveSpeed")->addModifier((void *)L"slow", -30);
	cout << "startskill";
}

void InvincibleEnemy::updateSkill()
{
}

void InvincibleEnemy::endSkill()
{
	cout << "endskill";
	getComponent<Collider>()->setOffset({ 0,0 });
	getComponent<Animator>()->playAnimation(L"invincibleEnd", false);
	stat->getStat(L"moveSpeed")->removeModifier((void *)L"slow");
}
