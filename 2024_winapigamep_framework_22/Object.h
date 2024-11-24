#pragma once
class Collider;
class Component;
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void update() abstract;
	virtual void lateUpdate();
	virtual void render(HDC _hdc) abstract;
	void componentrender(HDC _hdc);
public:
	void setPosition(Vector2 _vPos) { _position = _vPos; }
	void setSize(Vector2 _vSize) { _size = _vSize; }
	const Vector2& getPosition() const { return _position; }
	const Vector2& getSize() const { return _size; }
public:
	const bool& isDead() const { return _isDead; }
	void setDead() { _isDead = true; }
	void setTag(wstring _name) { _tag = _name; }
	const wstring& getTag() const { return _tag; }

private:
	bool _isDead;
	wstring _tag;
public:
	template<typename T>
	T* addComponent()
	{
		T* com = new T;
		com->SetOwner(this);
		_components.push_back(com);
		return com;
	}
	template<typename T>
	T* getComponent()
	{
		T* component = nullptr;
		for (Component* com : _components)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
protected:
	Vector2 _position;
	Vector2 _size;
	vector<Component*> _components;
};

