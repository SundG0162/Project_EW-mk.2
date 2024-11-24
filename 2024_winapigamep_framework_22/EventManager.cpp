#include "pch.h"
#include "EventManager.h"
#include "Object.h"
void EventManager::update()
{
	// 이전 프레임에서 등록해둔 
	for (Object* obj : _deadObjects)
	{
		if (obj != nullptr)
			delete obj;
	}
	_deadObjects.clear();

	for (auto& eve : _events)
		excute(eve);
	_events.clear();
}

void EventManager::deleteObject(Object* _pObj)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::DELETE_OBJECT;
	eve.object = _pObj;

	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::excute(const Event& _eve)
{
	switch (_eve.eventType)
	{
	case EVENT_TYPE::DELETE_OBJECT:
	{
		Object* pDeadObj = _eve.object;
		pDeadObj->setDead();
		_deadObjects.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::CREATE_OBJECT:
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		break;
	}
}
