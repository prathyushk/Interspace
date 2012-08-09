#ifndef __Hud_h_
#define __Hud_h_
#include <CEGUI.h>

class Hud
{
public:
	Hud(CEGUI::WindowManager* winMgr, CEGUI::System* system, CEGUI::Window* window);
	~Hud(void);
	void hide(void);
	void show(void);
	bool isVisible(void);
	CEGUI::Window* getGuiLayout(void);
private:
	bool visible;
	CEGUI::WindowManager* mWinMgr;
	CEGUI::System* mSystem;
	CEGUI::Window* mWindow;
	CEGUI::Window* guiLayout2;
	bool chatBoxClosed(const CEGUI::EventArgs&);
	bool sendChat(const CEGUI::EventArgs&);
	bool acrobatSelected(const CEGUI::EventArgs&);
	bool juggernautSelected(const CEGUI::EventArgs&);
	bool sniperSelected(const CEGUI::EventArgs&);
};

#endif