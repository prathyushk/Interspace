#include "Gui.h"
#include <CEGUI.h>
#include "MainMenu.h"
#include "Hud.h"
#include "Game.h"

Gui::Gui()
{
}

Gui::~Gui()
{
	mWindow->removeChildWindow(guiLayout);
	delete guiLayout;
}

CEGUI::Window* Gui::getLayout()
{
	return guiLayout;
}