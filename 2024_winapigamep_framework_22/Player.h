#pragma once
#include "WindowObject.h"
class CCTV;
class StatComponent;
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
private:
	StatComponent* _statComponent;
	CCTV* _cctv;
	bool _isBeaconSettingUp;
};

