#pragma once
#include "Upgrade.h"
class StatComponent;
class CameraStunUpgrade : public Upgrade
{
public:
	CameraStunUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~CameraStunUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[5] = { 0.2f, 0.4f, 0.6f, 0.8f, 1.f};
	StatComponent* _statComponent;
};

