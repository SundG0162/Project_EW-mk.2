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
		_callbacks.erase(
			std::remove_if(_callbacks.begin(), _callbacks.end(),
				[&](const Callback& currentListener) {
					return currentListener.target<void(Args...)>() == callback.target<void(Args...)>();
				}),
			_callbacks.end());
	}
	void invoke(Args... args)
	{
		for (const auto& callback : _callbacks)
		{
			callback(args...);
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