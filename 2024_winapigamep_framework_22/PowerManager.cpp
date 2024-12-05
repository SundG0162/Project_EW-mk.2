#include "pch.h"
#include "PowerManager.h"

void PowerManager::modifyPower(int value)
{
	int prev = _power;
	_power += value;
	OnPowerChangeEvent.invoke(prev, _power);
}
