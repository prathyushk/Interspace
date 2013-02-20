#ifndef __GuiManager_h__
#define __GuiManager_h__

class Interspace;
#include "Gui.h"
#include <Ogre.h>
#include <CEGUI.h>
#include <vector>

class GuiManager : public Ogre::Singleton<GuiManager>
{
public:
	GuiManager();
	~GuiManager();
	void openGui();
	void closeGui();
	void next();
	bool isVisible();
	Gui* getGui();

private:
	std::vector<Gui*> guis;
	int currentGui;
	CEGUI::Window* sheet;
	bool visible;
};

#endif