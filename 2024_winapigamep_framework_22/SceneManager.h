#pragma once
class Scene;
class SceneManager
{
	DECLARE_SINGLETON(SceneManager);
public:
	void init();
	void update();
	void render(HDC hDC);
public:
	void registerScene(const wstring& _sceneName, 
					std::shared_ptr<Scene> _scene);
	void loadScene(const wstring& _sceneName);
public:
	const std::shared_ptr<Scene>& getCurrentScene() const
	{
		return _currentScene;
	}
private:
	map<wstring, std::shared_ptr<Scene>> _sceneMap;
	std::shared_ptr<Scene> _currentScene;
};

