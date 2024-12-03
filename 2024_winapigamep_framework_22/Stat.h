#pragma once
class Stat
{
public:
	Stat(float baseValue);
	~Stat();
public:
	void addModifier(void* key, float value);
	void removeModifier(void* key);
public:
	float getBaseValue() { return _baseValue; }
	float getValue() { return _baseValue + _modifiedValue; };
private:
	float _baseValue;
	float _modifiedValue;
	map<void*, float> _modifierMap;
};

