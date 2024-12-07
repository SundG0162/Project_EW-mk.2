#pragma once
#include "Upgrade.h"
class StatComponent;
class TorchSizeUpgrade : public Upgrade
{
public:
	TorchSizeUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~TorchSizeUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	int _modifyValues[5] = { 30,60,90,120,150 };
	StatComponent* _statComponent;
};

