#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "InGameScene.h"
void SceneManager::init()
{
	_currentScene = nullptr;

	// ¾À µî·Ï
	registerScene(L"TitleScene", std::make_shared<TitleScene>());
	registerScene(L"InGameScene", std::make_shared<InGameScene>());
	loadScene(L"TitleScene");
}

void SceneManager::update()
{
	if (_currentScene == nullptr)
		return;
	_currentScene->update();
	_currentScene->lateUpdate();
}

void SceneManager::render(HDC hDC)
{
	if (_currentScene == nullptr)
		return;
	_currentScene->render(hDC);
}

void SceneManager::registerScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene)
{
	if (_sceneName.empty() || _scene == nullptr)
		return;
	_sceneMap.insert(_sceneMap.end(), {_sceneName, _scene});
}

void SceneManager::loadScene(const wstring& _sceneName)
{
	// ¾ÀÀÌ ÀÖÀ¸¸é
	if (_currentScene != nullptr)
	{
		_currentScene->release();
		_currentScene = nullptr;
	}

	auto iter = _sceneMap.find(_sceneName);
	if (iter != _sceneMap.end())
	{
		_currentScene = iter->second;
		_currentScene->init();
	}
}
