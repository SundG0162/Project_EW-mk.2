#pragma once
class Object;
struct Event
{
	EVENT_TYPE eventType;
	Object* object;
	LAYER objectLayer;
public:
	bool operator==(const Event& other)
	{
		return eventType == other.eventType && object == other.object;
	}
};
class EventManager
{
	DECLARE_SINGLETON(EventManager);
public:
	void update();
	void deleteObject(Object* _pObj);
	// todo..
private:
	void excute(const Event& _eve);
private:
	vector<Event> _events;
	vector<Object*> _deadObjects;
};