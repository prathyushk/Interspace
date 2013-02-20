#ifndef __Gui_h_
#define __Gui_h_

#include <CEGUI.h>
#include "Interspace.h"
#include <string>

class Gui
{
public:
	Gui(std::string inputName);
	virtual ~Gui();
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void load(CEGUI::Window* window) = 0;
	CEGUI::Window* getLayout();
	std::string getName();
protected:
	Interspace* engine;
	std::string name;
	CEGUI::WindowManager* mWinMgr;
	CEGUI::System* mSystem;
	CEGUI::Window* mWindow;
	CEGUI::Window* guiLayout;
};

#endif