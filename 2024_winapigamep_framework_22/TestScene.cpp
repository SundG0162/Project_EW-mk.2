#include "pch.h"
#include "TestScene.h"
#include "TestObject.h"

TestScene::TestScene()
{
	
}

TestScene::~TestScene()
{
}

void TestScene::init()
{
	TestObject* obj = new TestObject();
	addObject(obj, LAYER::DEFAULT);
}
