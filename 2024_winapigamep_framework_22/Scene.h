#pragma once
//#include "Object.h"
class Object; // Ŭ���� ���漱��
class Scene
{
public:
	Scene();
	virtual ~Scene(); // ���� �Ҹ���
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

