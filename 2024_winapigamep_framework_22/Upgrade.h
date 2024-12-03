#pragma once
#include "PlayerDevice.h"
class Upgrade : PlayerDevice
{
public:
	Upgrade(const wstring& text, int maxLevel);
	virtual ~Upgrade();
public:
	virtual void applyUpgrade() abstract;
private:
	wstring _text;
	int _currentLevel;
	int _maxLevel;
};