#ifndef __Gui_h__
#define __Gui_h__

#include <CEGUI.h>
#include "GameEngine.h"

class Gui
{
public:
	Gui();
	virtual ~Gui();
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void load(CEGUI::WindowManager* winMgr, CEGUI::System* system, CEGUI::Window* window,GameEngine* engine) = 0;
	CEGUI::Window* getLayout();
protected:
	GameEngine* engine;
	CEGUI::WindowManager* mWinMgr;
	CEGUI::System* mSystem;
	CEGUI::Window* mWindow;
	CEGUI::Window* guiLayout;
};

#endif