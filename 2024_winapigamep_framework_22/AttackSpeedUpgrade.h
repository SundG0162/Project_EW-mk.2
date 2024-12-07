#pragma once
#include "Upgrade.h"
class StatComponent;
class AttackSpeedUpgrade : public Upgrade
{
public:
	AttackSpeedUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~AttackSpeedUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[5] = { -0.15f, -0.3f, -0.45f, -0.6f, -0.75f };
	StatComponent* _statComponent;
};

