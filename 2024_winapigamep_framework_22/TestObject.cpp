#include "pch.h"
#include "TestObject.h"

void TestObject::update()
{
}

void TestObject::render(HDC hdc)
{
	TextOut(hdc, getPosition().x, getPosition().y, L"test", 5);
}
