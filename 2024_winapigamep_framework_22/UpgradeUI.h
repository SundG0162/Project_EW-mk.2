#pragma once
#include "UI.h"
class Player;
class Upgrade;
class UpgradeUI : public UI
{
public:
	UpgradeUI();
	~UpgradeUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void setUpgrade(Upgrade* upgrade);
private:
	vector<UI*> _uis;
	Player* _player;
};