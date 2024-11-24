#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
Scene::Scene()
{
}

Scene::~Scene()
{
	release();
}

void Scene::update()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < _objects[i].size(); ++j)
		{
			if (!_objects[i][j]->isDead())
				_objects[i][j]->update();
		}
	}
	
}

void Scene::lateUpdate()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (UINT j = 0; j < _objects[i].size(); ++j)
		{
			_objects[i][j]->lateUpdate();
		}
	}
}

void Scene::render(HDC _hdc)
{ 
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < _objects[i].size();)
		{
			if (!_objects[i][j]->isDead())
				_objects[i][j++]->render(_hdc);
			else
				_objects[i].erase(_objects[i].begin() + j);
		}
	}

}

void Scene::release()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (UINT j = 0; j < _objects[i].size(); ++j)
		{
			delete _objects[i][j];
		}
		_objects[i].clear();
	}
	GET_SINGLETON(CollisionManager)->checkReset();
}
