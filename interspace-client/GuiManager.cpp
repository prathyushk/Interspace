#include "GuiManager.h"
#include <CEGUI.h>
#include <Ogre.h>
#include "Interspace.h"
#include "Gui.h"
#include "MainMenu.h"
#include "Hud.h"
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

template<> GuiManager* Ogre::Singleton<GuiManager>::msSingleton = 0;

GuiManager::GuiManager()
	:currentGui(0), visible(true)
{
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
	sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().setGUISheet(sheet);
	guis.push_back(new MainMenu());
	guis.push_back(new Hud());
	guis.at(currentGui)->load(sheet);
}

GuiManager::~GuiManager()
{
}

Gui* GuiManager::getGui()
{
	return guis.at(currentGui);
}

void GuiManager::closeGui()
{
	if(visible)
	{
		guis.at(currentGui)->hide();
		visible = false;
	}
}

void GuiManager::openGui()
{
	if(!visible)
	{
		guis.at(currentGui)->show();
		visible = true;
	}
}

void GuiManager::next()
{
	if(currentGui + 1 < guis.size())
	{
		sheet->removeChildWindow(guis[currentGui]->getLayout());
		currentGui++;
		guis.at(currentGui)->load(sheet);
	}
}

bool GuiManager::isVisible()
{
	return visible;
}