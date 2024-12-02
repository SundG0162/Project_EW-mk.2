#pragma once
class UI;
class WindowUI;
class PopupManager
{
	DECLARE_SINGLETON(PopupManager)
	~PopupManager();
public:
	void addPopup(const wstring& key, UI* ui, const wstring& name);
	WindowUI* getPopup(const wstring& key);
	void popUp(const wstring& key, const Vector2& position, bool withTween);
	void close(const wstring& key, bool withTween);
private:
	map<wstring, WindowUI*> _uiMap;
};