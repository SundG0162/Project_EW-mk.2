#pragma once
#include "WindowObject.h"
#include "Action.h"
class CCTV;
class StatComponent;
class UpgradeComponent;
class Player : public WindowObject
{
public:
	Player(const Vector2& position, const Vector2& size);
	~Player();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	const CCTV* getCCTV() { return _cctv; }
public:
	void modifyHP(int value);
public:
	Action<int, int> OnHPChangeEvent;
	Action<PLAYER_ITEM> OnItemChangeEvent;
	Action<PLAYER_ITEM, int> OnItemUseEvent; // type, price
private:
	PLAYER_ITEM _currentItem;
	StatComponent* _statComponent;
	UpgradeComponent* _upgradeComponent;
	CCTV* _cctv;
	int _hp;
	int _maxHP;
	bool _isBeaconSettingUp;
};

