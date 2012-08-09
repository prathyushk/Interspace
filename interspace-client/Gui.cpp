#include "Gui.h"
#include <CEGUI.h>
#include "MainMenu.h"
#include "Hud.h"
#include "Game.h"

Gui::Gui(Game* app) : game(app), sheet(CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "CEGUIDemo/Sheet")), hud(NULL)
{
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
	CEGUI::System::getSingleton().setGUISheet(sheet);
	mainMenu = new MainMenu(CEGUI::WindowManager::getSingletonPtr(), CEGUI::System::getSingletonPtr(), sheet, game);
}

Gui::~Gui()
{
}

bool Gui::openHud()
{
	if(mainMenu)
	{
		sheet->removeChildWindow(mainMenu->getGuiLayout());
		//delete mainMenu;
		hud = new Hud(CEGUI::WindowManager::getSingletonPtr(), CEGUI::System::getSingletonPtr(), sheet);
	}
	return true;
}

bool Gui::openMenu()
{
	if(hud)
	{
		sheet->removeChildWindow(hud->getGuiLayout());
		//delete hud;
		mainMenu = new MainMenu(CEGUI::WindowManager::getSingletonPtr(), CEGUI::System::getSingletonPtr(), sheet, game);
	}
	return true;
}

bool Gui::isVisible()
{
	if(hud && mainMenu)
		return hud->isVisible() || mainMenu->isVisible();
	else if(hud)
		return hud->isVisible();
	else if(mainMenu)
		return mainMenu->isVisible();
	else return false;
}

bool Gui::isHud()
{
	if(hud)
		return true;
	else
		return false;
}

bool Gui::isMenu()
{
	if(mainMenu)
		return true;
	else
		return false;
}

Hud* Gui::getHud()
{
	return hud;
}

MainMenu* Gui::getMenu()
{
	return mainMenu;
}
