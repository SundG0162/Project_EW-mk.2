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
}

TitleScene::~TitleScene()
{
}

void TitleScene::init()
{
	_setuped = false;
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			if (_setuped == true)
			{
				GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
				return;
			}
			_setuped = true;
			WindowUI* textUI = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250 }, { 800, 300 }, WINDOW_TYPE::NEW, L"TitleText.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = textUI->getSize();
				text->setupFont(100);
				text->setPosition({ size.x / 2, size.y / 2 - 100 });
				text->setText(L"Defender of\n The Dawn");
				textUI->setUI(text);
			}

			WindowUI* explanationUI = new WindowUI({ SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 100 }, { 400, 100 }, WINDOW_TYPE::NEW, L"ExplanationText.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = explanationUI->getSize();
				text->setupFont(40);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"창을 닫아서 선택");
				explanationUI->setUI(text);
			}

			WindowUI* startBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Start.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = startBtn->getSize();
				text->setupFont(50);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"시작");
				startBtn->setUI(text);
			}
			startBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					GET_SINGLETON(EventManager)->changeScene(L"InGameScene");
				};

			WindowUI* tutorialBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Tutorial.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = tutorialBtn->getSize();
				text->setupFont(50);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"튜토리얼");
				tutorialBtn->setUI(text);
			}
			tutorialBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					GET_SINGLETON(EventManager)->changeScene(L"TutorialScene");
				};

			WindowUI* exitBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Exit.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = exitBtn->getSize();
				text->setupFont(50);
				text->setPosition({ size.x / 2, size.y / 3 });
				text->setText(L"나가기");
				exitBtn->setUI(text);
			}
			exitBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					PostQuitMessage(0);
				};

			textUI->getWindow()->setMoveable(false);
			textUI->getWindow()->setCloseable(false);
			explanationUI->getWindow()->setMoveable(true);
			explanationUI->getWindow()->setCloseable(false);
			startBtn->getWindow()->setMoveable(true);
			startBtn->getWindow()->setCloseable(false);
			tutorialBtn->getWindow()->setMoveable(true);
			tutorialBtn->getWindow()->setCloseable(false);
			exitBtn->getWindow()->setMoveable(true);
			exitBtn->getWindow()->setCloseable(false);
			textUI->getWindow()->openTween(0.f);
			explanationUI->getWindow()->openTween(0.f);
			startBtn->getWindow()->openTween(0.f);
			tutorialBtn->getWindow()->openTween(0.f);
			exitBtn->getWindow()->openTween(0.f);
			textUI->getWindow()->setPriority(-1);
			GET_SINGLETON(EventManager)->createObject(textUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(explanationUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(startBtn, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(tutorialBtn, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(exitBtn, LAYER::UI);
		};
}