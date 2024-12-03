#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "WindowObject.h"
#include "NewWindow.h"
#include "CollisionManager.h"
Scene::Scene()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < _objects[i].size(); ++j)
		{
			if (!_objects[i][j]->isDead())
				_objects[i][j]->init();
		}
	}
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

void Scene::render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < _objects[i].size();)
		{
			if (!_objects[i][j]->isDead())
			{
				Object* obj = _objects[i][j++];
				WindowObject* win = dynamic_cast<WindowObject*>(obj);
				if (win)
				{
					if (win->getType() == WINDOW_TYPE::COPY)
					{
						win->render(hDC);
					}
					else
					{
						win->render(dynamic_cast<NewWindow*>(win->getWindow())->getBackDC());
					}
				}
				else
					obj->render(hDC);
			}
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
