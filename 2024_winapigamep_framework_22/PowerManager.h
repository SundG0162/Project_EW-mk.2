#pragma once
#include "Action.h"
class PowerManager
{
	DECLARE_SINGLETON(PowerManager)
public:
	void modifyPower(int value);
public:
	int getPower() { return _power; }
	void setPower(int power) { _power = power; }
public:
	Action<int, int> OnPowerChangeEvent;
private:
	int _power;
};