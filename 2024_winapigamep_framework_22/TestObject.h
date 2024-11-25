#pragma once
#include "WindowObject.h"
class TestObject : public WindowObject
{
public:
	TestObject();
	~TestObject();
public:
	void update() override;
	void render(HDC hDC) override;
};

