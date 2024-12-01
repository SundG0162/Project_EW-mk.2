#pragma once
#include "UI.h"
class PanelUI : public UI
{
public:
	PanelUI();
	~PanelUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void addUI(UI* ui) { _uis.push_back(ui); }
	void removeUI(UI* ui) 
	{
		auto iter = std::find(_uis.begin(), _uis.end(), ui);
		if (iter != _uis.end())
		{
			_uis.erase(iter);
			delete& iter;
		}
	}
private:
	vector<UI*> _uis;
};

