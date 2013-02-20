#include "Gui.h"
#include <CEGUI.h>
#include "Interspace.h"
#include <string>

Gui::Gui(std::string inputName)
	:name(inputName)
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

std::string Gui::getName()
{
	return name;
}