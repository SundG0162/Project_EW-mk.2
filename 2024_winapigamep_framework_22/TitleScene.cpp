#include "pch.h"
#include "TitleScene.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "SceneManager.h"
#include "NewWindow.h"
#include "Core.h"

TitleScene::TitleScene()
{
	_textUI = nullptr;
	_explanationUI = nullptr;
	_startBtn = nullptr;
	_tutorialBtn = nullptr;
	_exitBtn = nullptr;
}

TitleScene::~TitleScene()
{
}

void TitleScene::init()
{
	_setuped = false;
	_setuped = false;
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			if (_setuped == true)
			{
				GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
				return;
			}
			_textUI = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250 }, { 800, 300 }, WINDOW_TYPE::NEW, L"TitleText.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = _textUI->getSize();
				text->setupFont(100);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"ProjectEW");
				_textUI->setUI(text);
			}

			_explanationUI = new WindowUI({ SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 100 }, { 400, 100 }, WINDOW_TYPE::NEW, L"ExplanationText.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = _explanationUI->getSize();
				text->setupFont(40);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"창을 닫아서 선택");
				_explanationUI->setUI(text);
			}

			_startBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Start.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = _startBtn->getSize();
				text->setupFont(50);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"시작");
				_startBtn->setUI(text);
			}
			_startBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					GET_SINGLETON(EventManager)->changeScene(L"InGameScene");
				};

			_tutorialBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Tutorial.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = _tutorialBtn->getSize();
				text->setupFont(50);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"튜토리얼");
				_tutorialBtn->setUI(text);
			}
			_tutorialBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					GET_SINGLETON(EventManager)->changeScene(L"TutorialScene");
				};

			_exitBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Exit.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = _exitBtn->getSize();
				text->setupFont(50);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"나가기");
				_exitBtn->setUI(text);
			}
			_exitBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					PostQuitMessage(0);
				};

			_textUI->getWindow()->setMoveable(false);
			_textUI->getWindow()->setCloseable(false);
			_explanationUI->getWindow()->setMoveable(true);
			_explanationUI->getWindow()->setCloseable(false);
			_startBtn->getWindow()->setMoveable(true);
			_startBtn->getWindow()->setCloseable(false);
			_tutorialBtn->getWindow()->setMoveable(true);
			_tutorialBtn->getWindow()->setCloseable(false);
			_exitBtn->getWindow()->setMoveable(true);
			_exitBtn->getWindow()->setCloseable(false);
			GET_SINGLETON(EventManager)->createObject(_textUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_explanationUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_startBtn, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_tutorialBtn, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_exitBtn, LAYER::UI);
		};
}