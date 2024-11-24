#include "pch.h"
#include "TestScene.h"
#include "TestObject.h"

TestScene::TestScene()
{
	TestObject* obj = new TestObject();
	addObject(obj, LAYER::DEFAULT);
}

TestScene::~TestScene()
{
}

void TestScene::init()
{
}
