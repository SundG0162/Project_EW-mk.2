#pragma once
#include "Object.h"
class TestObject : public Object
{
public:
	TestObject();
	~TestObject();
public:
	void update() override;
	void render(HDC hDC) override;
};

