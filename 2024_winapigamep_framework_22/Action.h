#pragma once
#include <functional>
template<typename... Args>
class Action
{
	using Listener = std::function<void(Args...)>;
public:
	Action() {}
	~Action() {}
public:
	void operator+= (const Listener& callback)
	{
		addListener(callback);
	}
	void operator-= (const Listener& callback)
	{
		removeListener(callback);
	}
public:
	void addListener(const Listener& callback)
	{
		_callbacks.push_back(callback);
	}
	void removeListener(const Listener& callback)
	{
		_callbacks.erase(
			std::remove_if(_callbacks.begin(), _callbacks.end(),
				[&](const Listener& currentListener) {
					return currentListener.target<void(Args...)>() == callback.target<void(Args...)>();
				}),
			_callbacks.end());
	}
	void invoke(Args... args)
	{
		for (const auto& listener : _callbacks)
		{
			listener(args...);
		}
	}
	void clear()
	{
		_callbacks.clear();
	}

private:
	std::vector<Listener> _callbacks;
};