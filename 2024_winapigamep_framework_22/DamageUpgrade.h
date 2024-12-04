#pragma once
#include "Upgrade.h"
class StatComponent;
class DamageUpgrade : public Upgrade
{
public:
	DamageUpgrade(Sprite* icon, const wstring& title, const wstring& description, int maxLevel);
	~DamageUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	int _modifyValues[5] = { 1, 2, 3, 4, 5 };
	StatComponent* _statComponent;
};

