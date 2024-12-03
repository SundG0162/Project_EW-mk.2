#pragma once
#include "UI.h"
class Player;
class Upgrade;
class UpgradeUI : UI
{
public:
	UpgradeUI();
	~UpgradeUI();
public:
	void setUpgrade(Upgrade* upgrade);
private:
	Player* _player;
};