#pragma once
#include "Upgrade.h"
class StatComponent;
class CameraDamageUpgrade : public Upgrade
{
public:
	CameraDamageUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~CameraDamageUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[5] = { 3, 6, 9, 12, 15 };
	StatComponent* _statComponent;
};

