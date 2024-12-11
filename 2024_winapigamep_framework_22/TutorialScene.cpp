#include "pch.h"
#include "TutorialScene.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "SceneManager.h"
#include "Core.h"
#include "NewWindow.h"

TutorialScene::TutorialScene()
{
	_currentIndex = -1;
	_panelSize = { 512,512 };
	_panelPosition = { (float)SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - _panelSize.y / 6 };
	_setuped = false;
	_panelUI = nullptr;
	_textUI = nullptr;
	for (int i = 1; i <= 6; i++)
	{
		wstring name = std::format(L"TutorialPanel{0}", i);
		_panelSprites.push_back(GET_SINGLETON(ResourceManager)->getSprite(name));
	}
	_tutorialTexts.push_back(L"You can move CCTV.exe around via WASD to explore the neighborhood.\nCCTV.exe is a basic attack vector.");
	_tutorialTexts.push_back(L"In-game, you can get power by killing enemies or spinning a generator. \nPower allows you to upgrade various devices.");
	_tutorialTexts.push_back(L"You can select items by pressing the number keys and use the \nspace and enter keys.");
	_tutorialTexts.push_back(L"CCTV.exe can be used to illuminate enemies or catch viruses through items.\n Oh, and as a side note, each time CCTV attacks, it costs power.");
	_tutorialTexts.push_back(L"The game will end if the enemy reaches the monitor more than 3 times.");
	_tutorialTexts.push_back(L"You can open the generator window by pressing F during the game\nbut be careful not to open it incorrectly as it will render the CCTV inoperable.");
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::init()
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
			_panelUI = new WindowUI(_panelPosition, _panelSize, WINDOW_TYPE::NEW, L"TutorialPanel.exe");
			ImageUI* image = new ImageUI(nullptr);
			image->setPosition({ _panelSize.x / 2, _panelSize.y / 2 });
			image->getComponent<SpriteRenderer>()->setScale({ 3,3 });
			_panelUI->setUI(image);
			_textUI = new WindowUI({ (int)_panelPosition.x, SCREEN_HEIGHT - 150 }, { SCREEN_WIDTH,300 }, WINDOW_TYPE::NEW, L"TutorialText.exe");
			TextUI* text = new TextUI();
			text->setupFont(40);
			_textUI->setUI(text);
			text->setPosition({ SCREEN_WIDTH / 2,(int)_textUI->getSize().y / 4 });
			_textUI->getWindow()->setMoveable(false);
			_textUI->getWindow()->setCloseable(false);
			WindowUI* nextBtn = new WindowUI({ _panelPosition.x + _panelSize.x / 1.5f, _panelPosition.y - _panelSize.y / 2 - 50 }, { 300,70 }, WINDOW_TYPE::NEW, L"Next.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = nextBtn->getSize();
				text->setupFont(30);
				text->setPosition({ size.x / 2,size.y / 4 });
				text->setText(L"Close to next");
				nextBtn->setUI(text);
			}
			nextBtn->getWindow()->setPriority(UI_PRIORITY + 2);
			nextBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					nextTutorial();
				};

			WindowUI* exitBtn = new WindowUI({ _panelPosition.x - _panelSize.x, _panelPosition.y - _panelSize.y / 2 - 100 }, { 300,70 }, WINDOW_TYPE::NEW, L"Exit.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = nextBtn->getSize();
				text->setupFont(30);
				text->setPosition({ size.x / 2,size.y / 4 });
				text->setText(L"Close to exit");
				exitBtn->setUI(text);
			}
			exitBtn->getWindow()->setPriority(UI_PRIORITY + 2);
			exitBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
				};

			_panelUI->getWindow()->setMoveable(false);
			_panelUI->getWindow()->setCloseable(false);
			_textUI->getWindow()->setMoveable(false);
			_textUI->getWindow()->setCloseable(false);
			nextBtn->getWindow()->setMoveable(true);
			nextBtn->getWindow()->setCloseable(false);
			exitBtn->getWindow()->setMoveable(true);
			exitBtn->getWindow()->setCloseable(false);
			_currentIndex = -1;
			nextTutorial();
			GET_SINGLETON(EventManager)->createObject(_panelUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_textUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(nextBtn, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(exitBtn, LAYER::UI);
		};
}

void TutorialScene::nextTutorial()
{
	_currentIndex++;
	if (_currentIndex == _tutorialTexts.size())
	{
		GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
		return;
	}
	else if (_currentIndex > _tutorialTexts.size())
		return;
	_panelUI->getUI<ImageUI>()->setSprite(_panelSprites[_currentIndex]);
	_textUI->getUI<TextUI>()->setText(_tutorialTexts[_currentIndex]);
}