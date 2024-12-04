#include "pch.h"
#include "UpgradeUI.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "PlayerManager.h"
#include "TextUI.h"

UpgradeUI::UpgradeUI()
{
	_player = GET_SINGLETON(PlayerManager)->getPlayer();
	_position = { 160, 240};
	_size = { 320, 480 };
	Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(L"UpgradeCard");
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	renderer->setSprite(sprite);
	renderer->setScale({ _size.x / 32, _size.y / 48 });
	TextUI* title = new TextUI();
	title->setupFont(L"Galmuri9 Regular", 27, 400);
	title->setText(L"Im타이틀");
	title->setPosition({ _position.x, _position.y - 220});
	TextUI* description = new TextUI();
	description->setupFont(L"Galmuri9 Regular", 18, 400);
	description->setText(L"나는 설명이에요.\n엄준식");
	description->setPosition(_position);
	_uis.push_back(title);
	_uis.push_back(description);
}

UpgradeUI::~UpgradeUI()
{
}

void UpgradeUI::setUpgrade(Upgrade* upgrade)
{
}

void UpgradeUI::update()
{
	for (UI* ui : _uis)
	{
		ui->update();
	}
}

void UpgradeUI::render(HDC hdc)
{
	componentRender(hdc);
	for (UI* ui : _uis)
	{
		ui->render(hdc);
	}
}
