#include "pch.h"
#include "PanelUI.h"

PanelUI::PanelUI()
{
}

PanelUI::~PanelUI()
{
}

void PanelUI::update()
{
	for (UI* ui : _uis)
		if (ui && !ui->isDead())
			ui->update();
}

void PanelUI::render(HDC hdc)
{
	for (UI* ui : _uis)
		if (ui && !ui->isDead())
			ui->render(hdc);
}
