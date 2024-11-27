#pragma once
class Window;
class WindowManager
{
	DECLARE_SINGLETON(WindowManager)
	~WindowManager();
public:
	void update();
	void render();
public:
	void addWindow(Window* window) { _windows.push_back(window); }
	void removeWindow(Window* window)
	{
		auto iter = std::find(_windows.begin(), _windows.end(), window);
		if (iter != _windows.end())
			_windows.erase(iter);
	}
private:
	vector<Window*> _windows;
};

