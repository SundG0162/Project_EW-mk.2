#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "InGameScene.h"
#include "EnemyTestScene.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "Core.h"
void SceneManager::init()
{
	_currentScene = nullptr;

	// �� ���
	registerScene(L"TitleScene", std::make_shared<TitleScene>());
	registerScene(L"InGameScene", std::make_shared<InGameScene>());
	registerScene(L"EnemyTestScene", std::make_shared<EnemyTestScene>());
	loadScene(L"InGameScene");
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
	GET_SINGLETON(Core)->setStopLoop(true);
	if (_currentScene != nullptr)
	{
		_currentScene->release();
		_currentScene = nullptr;
	}
	GET_SINGLETON(EventManager)->deadObjectClear();
	auto iter = _sceneMap.find(_sceneName);
	if (iter != _sceneMap.end())
	{
		_currentScene = iter->second;
		_currentScene->init();
	}
	GET_SINGLETON(Core)->setStopLoop(false);
}
