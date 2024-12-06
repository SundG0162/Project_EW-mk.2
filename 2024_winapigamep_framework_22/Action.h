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
		_callbacks.erase(
			std::remove_if(_callbacks.begin(), _callbacks.end(),
				[](const std::function<void(Args...)>& func)
				{
					return !func;
				}),
			_callbacks.end()
		);

		for (auto& callback : _callbacks)
		{
			if (callback)
			{
				callback(args...);
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