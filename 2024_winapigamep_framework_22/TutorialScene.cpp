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
#include "NewWindow.h"

TutorialScene::TutorialScene()
{
	_currentIndex = -1;
	_panelSize = { 512,512 };
	_panelPosition = { (float)SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - _panelSize.y / 6 };
	_textUI = nullptr;
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::init()
{
	for (int i = 1; i <= 5; i++)
	{
		wstring name = std::format(L"TutorialPanel{0}", i);
		_panelSprites.push_back(GET_SINGLETON(ResourceManager)->getSprite(name));
	}
	_tutorialTexts.push_back(L"WASD를 통해 CCTV.exe를 움직여 근처를 탐색할 수 있습니다.");
	_tutorialTexts.push_back(L"인게임에서 바이러스를 잡아 전력을 얻을 수 있습니다.\n전력을 통해 각종 기기를 업그레이드 할 수 있습니다.");
	_tutorialTexts.push_back(L"숫자 키를 눌러 아이템을 선택하고\n스페이스, 엔터키를 통해\n사용할 수 있습니다.");
	_tutorialTexts.push_back(L"CCTV.exe로 적을 비추거나 아이템을 통해 바이러스를 잡을 수 있습니다.");
	_tutorialTexts.push_back(L"바이러스가 모니터에 3번 이상 도달할 경우 게임은 종료됩니다.");
	_panelUI = new WindowUI(_panelPosition, _panelSize, WINDOW_TYPE::NEW, L"TutorialPanel.exe");
	ImageUI* image = new ImageUI(nullptr);
	image->setPosition({ _panelSize.x / 2, _panelSize.y / 2 });
	image->getComponent<SpriteRenderer>()->setScale({ 3,3 });
	_panelUI->setUI(image);
	_textUI = new WindowUI({ (int)_panelPosition.x, SCREEN_HEIGHT - 150 }, { SCREEN_WIDTH,300 }, WINDOW_TYPE::NEW, L"TutorialText.exe");
	TextUI* text = new TextUI();
	text->setupFont(L"Galmuri9 Regular", 40, 400);
	_textUI->setUI(text);
	text->setPosition({ SCREEN_WIDTH / 2,(int)_textUI->getSize().y / 4});
	_textUI->getWindow()->setMoveable(false);
	_textUI->getWindow()->setCloseable(false);
	_nextBtn = new WindowUI({ _panelPosition.x + _panelSize.x / 1.5f, _panelPosition.y - _panelSize.y / 2 - 50 }, { 300,70 }, WINDOW_TYPE::NEW, L"Next.exe");
	{
		TextUI* text = new TextUI();
		Vector2 size = _nextBtn->getSize();
		text->setupFont(L"Galmuri9 Regular", 20, 400);
		text->setPosition({ size.x / 2,size.y / 4 });
		text->setText(L"닫아서 다음으로");
		_nextBtn->setUI(text);
	}
	_nextBtn->getWindow()->setPriority(UI_PRIORITY + 2);
	_nextBtn->getWindow()->OnTryWindowCloseEvent += [this]()
		{
			nextTutorial();
		};

	_exitBtn = new WindowUI({ _panelPosition.x - _panelSize.x, _panelPosition.y - _panelSize.y / 2 - 100 }, { 300,70 }, WINDOW_TYPE::NEW, L"Exit.exe");
	{
		TextUI* text = new TextUI();
		Vector2 size = _nextBtn->getSize();
		text->setupFont(L"Galmuri9 Regular", 20, 400);
		text->setPosition({ size.x / 2,size.y / 4 });
		text->setText(L"닫아서 나가기");
		_exitBtn->setUI(text);
	}
	_exitBtn->getWindow()->setPriority(UI_PRIORITY + 2);
	_exitBtn->getWindow()->OnTryWindowCloseEvent += [this]()
		{
			GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
		};

	_panelUI->getWindow()->setMoveable(false);
	_panelUI->getWindow()->setCloseable(false);
	_textUI->getWindow()->setMoveable(false);
	_textUI->getWindow()->setCloseable(false);
	_nextBtn->getWindow()->setMoveable(true);
	_nextBtn->getWindow()->setCloseable(false);
	_exitBtn->getWindow()->setMoveable(true);
	_exitBtn->getWindow()->setCloseable(false);
	_currentIndex = -1;
	addObject(_panelUI, LAYER::UI);
	addObject(_textUI, LAYER::UI);
	addObject(_nextBtn, LAYER::UI);
	addObject(_exitBtn, LAYER::UI);
	nextTutorial();
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
	HDC hdc = ((NewWindow*)_textUI->getWindow())->getBackDC();
	PatBlt(hdc, 0, 0, _textUI->getSize().x, _textUI->getSize().y, BLACKNESS);
}