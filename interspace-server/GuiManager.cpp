#include "GuiManager.h"
#include <CEGUI.h>
#include <Ogre.h>
#include "GameEngine.h"
#include "Gui.h"
#include "MainMenu.h"
#include "Hud.h"
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

GuiManager::GuiManager(GameEngine* inputEngine)
	:engine(inputEngine), guis(new std::vector<Gui*>()), currentGui(0), visible(false)
{
	CEGUI::OgreRenderer::bootstrapSystem(*inputEngine->getRenderWindow());
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
	CEGUI::System::getSingleton().setGUISheet(sheet);
	guis->push_back(new MainMenu());
	guis->push_back(new Hud());
	guis->at(currentGui)->load(CEGUI::WindowManager::getSingletonPtr(),CEGUI::System::getSingletonPtr(),sheet,engine);
}

GuiManager::~GuiManager()
{
}

Gui* GuiManager::getGui()
{
	return guis->at(currentGui);
}

void GuiManager::closeGui()
{
	if(visible)
	{
		guis->at(currentGui)->hide();
		visible = false;
	}
}

void GuiManager::openGui()
{
	if(!visible)
	{
		guis->at(currentGui)->show();
		visible = true;
	}
}

bool GuiManager::isVisible()
{
	return visible;
}