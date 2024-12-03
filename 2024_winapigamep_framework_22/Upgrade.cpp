#include "pch.h"
#include "Upgrade.h"

Upgrade::Upgrade(const wstring& text, int maxLevel)
{
	_text = text;
	_maxLevel = maxLevel;
	_currentLevel = 0;
}

Upgrade::~Upgrade()
{
}
