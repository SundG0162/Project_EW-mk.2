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
	float _modifyValues[5] = { 3, 6, 10, 14, 19 };
	StatComponent* _statComponent;
};

