#ifndef __Gui_h_
#define __Gui_h_

class Game;
#include <CEGUI.h>
#include "MainMenu.h"
#include "Hud.h"

class Gui
{
public:
	Gui(Game*);
	~Gui(void);
	bool openMenu(void);
	bool openHud(void);
	bool isVisible(void);
	bool isHud(void);
	bool isMenu(void);
	Hud* getHud(void);
	MainMenu* getMenu(void);
private:
	Game* game;
	Hud* hud;
	MainMenu* mainMenu;
	CEGUI::Window* sheet;
};

#endif