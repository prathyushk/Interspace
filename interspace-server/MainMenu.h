#ifndef __MainMenu_h__
#define __MainMenu_h__

#include <CEGUI.h>
#include "Gui.h"
#include "GameEngine.h"

class MainMenu : public Gui
{
public:
	MainMenu();
	~MainMenu();
	void hide();
	void show();
	void load(CEGUI::WindowManager* winMgr, CEGUI::System* system, CEGUI::Window* window,GameEngine* engine);
private:
	bool startButtonClicked(const CEGUI::EventArgs&);
	bool optionsButtonClicked(const CEGUI::EventArgs&);
	bool creditsButtonClicked(const CEGUI::EventArgs&);
	bool goButtonClicked(const CEGUI::EventArgs&);
	bool yesTutorial(const CEGUI::EventArgs&);
	bool noTutorial(const CEGUI::EventArgs&);
	bool closeOptions(const CEGUI::EventArgs&);
	bool closeLogin(const CEGUI::EventArgs&);
};

#endif