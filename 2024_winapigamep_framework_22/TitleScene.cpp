#include "pch.h"
#include "TitleScene.h"
#include "TextUI.h"

void TitleScene::init()
{
	{
		TextUI* ui = new TextUI({ 1500, 500 }, {200, 1000});
		addObject(ui, LAYER::UI);
		ui->openTween();
	}
}