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
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::init()
{
	_setuped = false;
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
			if (_setuped) return;
			_setuped = true;
			for (int i = 1; i <= 6; i++)
			{
				wstring name = std::format(L"TutorialPanel{0}", i);
				_panelSprites.push_back(GET_SINGLETON(ResourceManager)->getSprite(name));
			}
			_tutorialTexts.push_back(L"WASD�� ���� CCTV.exe�� ������ ��ó�� Ž���� �� �ֽ��ϴ�.");
			_tutorialTexts.push_back(L"�ΰ��ӿ��� ���̷����� ��ų� �����⸦ ���� ������ ���� �� �ֽ��ϴ�.\n������ ���� ���� ��⸦ ���׷��̵� �� �� �ֽ��ϴ�.");
			_tutorialTexts.push_back(L"���� Ű�� ���� �������� �����ϰ�\n�����̽�, ����Ű�� ����\n����� �� �ֽ��ϴ�.");
			_tutorialTexts.push_back(L"CCTV.exe�� ���� ���߰ų� �������� ���� ���̷����� ���� �� �ֽ��ϴ�.\n��, ����� CCTV�� �����Ҷ����� ������ �Ҹ�˴ϴ�.");
			_tutorialTexts.push_back(L"���̷����� ����Ϳ� 3�� �̻� ������ ��� ������ ����˴ϴ�.");
			_tutorialTexts.push_back(L"���� ���߿� FŰ�� ���� ������ â�� �� �� �ֽ��ϴ�.\n������ �����°� ������ �߸� �����ٰ� CCTV�� ���� �Ұ��������� �����ϼ���.");
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
			_nextBtn = new WindowUI({ _panelPosition.x + _panelSize.x / 1.5f, _panelPosition.y - _panelSize.y / 2 - 50 }, { 300,70 }, WINDOW_TYPE::NEW, L"Next.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = _nextBtn->getSize();
				text->setupFont(30);
				text->setPosition({ size.x / 2,size.y / 4 });
				text->setText(L"�ݾƼ� ��������");
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
				text->setupFont(30);
				text->setPosition({ size.x / 2,size.y / 4 });
				text->setText(L"�ݾƼ� ������");
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
			nextTutorial();
			GET_SINGLETON(EventManager)->createObject(_panelUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_textUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_nextBtn, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_exitBtn, LAYER::UI);
		};
}

void TutorialScene::release()
{
	Scene::release();
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