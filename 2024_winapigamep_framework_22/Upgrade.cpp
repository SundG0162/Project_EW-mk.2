#include "pch.h"
#include "Upgrade.h"

Upgrade::Upgrade(Sprite* icon, const wstring& title, const wstring& description, int maxLevel)
{
	_icon = icon;
	_title = title;
	_description = description;
	_maxLevel = maxLevel;
	_currentLevel = 0;
}

Upgrade::~Upgrade()
{
}
