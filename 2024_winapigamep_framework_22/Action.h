#pragma once
#include <functional>
template<typename... Args>
class Action
{
	using Callback = std::function<void(Args...)>;
public:
	Action() {}
	~Action() {}
public:
	void operator+= (const Callback& callback)
	{
		addListener(callback);
	}
	void operator-= (const Callback& callback)
	{
		removeListener(callback);
	}
public:
	void addListener(const Callback& callback)
	{
		_callbacks.push_back(callback);
	}
	void removeListener(const Callback& callback)
	{
		auto it = std::find_if(_callbacks.begin(), _callbacks.end(),
			[&](const Callback& currentListener)
			{
				return currentListener.target<void(Args...)>() == callback.target<void(Args...)>();
			});

		if (it != _callbacks.end())
		{
			_callbacks.erase(it);
		}
	}
	void invoke(Args... args)
	{
		for (size_t i = 0; i < _callbacks.size();) {
			if (_callbacks[i]) {
				_callbacks[i](args...);
				++i;
			}
			else {
				_callbacks.erase(_callbacks.begin() + i);
			}
		}
	}
	void clear()
	{
		_callbacks.clear();
	}
	int count()
	{
		return _callbacks.size();
	}
private:
	std::vector<Callback> _callbacks;
};