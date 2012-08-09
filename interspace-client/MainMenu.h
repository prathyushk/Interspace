#ifndef __MainMenu_h_
#define __MainMenu_h_

class Game;
#include <CEGUI.h>

class MainMenu
{
public:
	MainMenu(CEGUI::WindowManager*, CEGUI::System*, CEGUI::Window*, Game*);
	~MainMenu(void);
	void hide(void);
	void show(void);
	bool isVisible(void);
	void setVisible(bool);
	CEGUI::Window* getGuiLayout(void);
private:
	Game* mApp;
	bool visible;
	CEGUI::WindowManager* mWinMgr;
	CEGUI::System* mSystem;
	CEGUI::Window* mWindow;
	CEGUI::Window* guiLayout;
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