#pragma once
#include "WindowObject.h"
class Collider;
class CCTV : public WindowObject
{
public:
	CCTV(const Vector2& position, const Vector2& size);
	~CCTV();
public:
	void init() override;
	void update() override;
	void render(HDC hdc) override;
public:
	void handleOnCollisionEnter(Collider* other);
	void handleOnCollisionExit(Collider* other);
public:
	void localMove(const Vector2& move);
private:
	vector<Object*> _targets;
};