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

	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 2 }, { 32,32 }, 6);
		addComponent<Animator>()->
			createAnimation(L"invincible", vecsprite, 0.5f * 6);
	}
	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 3 }, { 32,32 }, 2);
		getComponent<Animator>()->
			createAnimation(L"move", vecsprite, 0.5f * 2);
	}
	getComponent<Animator>()->playAnimation(L"move", true);

	stat->getStat(L"moveSpeed")->setValue(40.f);
	stat->getStat(L"CoolTime")->setValue(1.f);
	stat->getStat(L"SkilTime")->setValue(2.f);
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
	getComponent<Animator>()->playAnimation(L"invincible", false);
	stat->getStat(L"moveSpeed")->addModifier((void *)L"slow", -30);
}

void InvincibleEnemy::updateSkill()
{
}

void InvincibleEnemy::endSkill()
{
	getComponent<Collider>()->setOffset({ 0,0 });
	getComponent<Animator>()->playAnimation(L"move", true);
	stat->getStat(L"moveSpeed")->removeModifier((void *)L"slow");
}
