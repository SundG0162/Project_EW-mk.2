#pragma once
#include <functional>
template<typename... Args>
class Action
{
public:
    void operator+=(std::function<void(Args...)> func) 
    {
        _callbacks.push_back(func);
    }
    void operator()(Args... args) 
    {
        invoke(args...);
    }
public:
    void invoke(Args... args) 
    {
        for (auto& callback : _callbacks) 
        {
            callback(args...);
        }
    }
    void Clear() 
    {
        _callbacks.clear();
    }
private:
    std::vector<std::function<void(Args...)>> _callbacks;
};