#pragma once
#include "Upgrade.h"
class StatComponent;
class CameraSizeUpgrade : public Upgrade
{
public:
	CameraSizeUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~CameraSizeUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[5] = { 30, 60, 90, 120, 150 };
	StatComponent* _statComponent;
};