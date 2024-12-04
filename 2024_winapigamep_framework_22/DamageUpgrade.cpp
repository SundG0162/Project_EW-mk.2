#include "pch.h"
#include "DamageUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

DamageUpgrade::DamageUpgrade(Sprite* icon, const wstring& title, const wstring& description, int maxLevel) : Upgrade(icon, title, description, maxLevel)
{
}

DamageUpgrade::~DamageUpgrade()
{
}

void DamageUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void DamageUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"Damage")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
