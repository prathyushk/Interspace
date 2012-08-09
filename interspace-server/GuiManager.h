#ifndef __GuiManager_h__
#define __GuiManager_h__

class GameEngine;
#include "Gui.h"
#include <CEGUI.h>
#include <vector>

class GuiManager
{
public:
	GuiManager(GameEngine* engine);
	~GuiManager();
	void openGui();
	void closeGui();
	bool isVisible();
	Gui* getGui();

private:
	GameEngine* engine;
	std::vector<Gui*>* guis;
	int currentGui;
	CEGUI::Window* sheet;
	bool visible;
};

#endif