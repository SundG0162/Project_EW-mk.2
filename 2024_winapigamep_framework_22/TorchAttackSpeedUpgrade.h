#pragma once
#include "Upgrade.h"
class StatComponent;
class TorchAttackSpeedUpgrade : public Upgrade
{
public:
	TorchAttackSpeedUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~TorchAttackSpeedUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[3] = { -0.15f,-0.3f,-0.45f };
	StatComponent* _statComponent;
};

