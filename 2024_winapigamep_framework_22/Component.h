#pragma once
class Object;
class Component
{
public:
	Component();
	virtual ~Component();
public:
	virtual void lateUpdate() abstract;
	virtual void render(HDC _hdc) abstract;
public:
	void setOwner(Object* _owner) { _owner = _owner; }
	Object* getOwner() const { return _owner; }
private:
	Object* _owner;
};

