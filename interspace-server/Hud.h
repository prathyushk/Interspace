#ifndef __Hud_h__
#define __Hud_h__

#include <CEGUI.h>
#include "Gui.h"
#include "GameEngine.h"

class Hud : public Gui
{
public:
	Hud();
	~Hud();
	void hide();
	void show();
	void load(CEGUI::WindowManager* winMgr, CEGUI::System* system, CEGUI::Window* window,GameEngine* engine);
private:
	bool chatBoxClosed(const CEGUI::EventArgs&);
	bool sendChat(const CEGUI::EventArgs&);
	bool acrobatSelected(const CEGUI::EventArgs&);
	bool juggernautSelected(const CEGUI::EventArgs&);
	bool sniperSelected(const CEGUI::EventArgs&);
};

#endif