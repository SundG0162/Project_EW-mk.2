#pragma once
//#include "Object.h"
class Object; // 클래스 전방선언
class Scene
{
public:
	Scene();
	virtual ~Scene(); // 가상 소멸자
public:
	virtual void init() abstract;
	virtual void update();
	virtual void lateUpdate();
	virtual void render(HDC hDC);
	virtual void release();
public:
	void addObject(Object* _obj, LAYER _type)
	{
		_objects[(UINT)_type].push_back(_obj);
	}
	const vector<Object*>& getLayerObjects(LAYER _type)
	{
		return _objects[(UINT)_type];
	}
private:
	vector<Object*> _objects[(UINT)LAYER::END];
};

