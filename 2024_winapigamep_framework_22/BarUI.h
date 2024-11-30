#pragma once
#include "UI.h"
class BarUI : public UI
{
public:
	BarUI(const Vector2& position, const Vector2& size);
	~BarUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void setFillAmount(float value);
	void setVertical(bool vertical) { _isVertical = vertical; }
private:
	float _fillAmount;
	bool _isVertical;
	bool _isFinished;
};

