#ifndef __MainMenu_h_
#define __MainMenu_h_

class Interspace;
#include <CEGUI.h>
#include "Gui.h"
#include <string>

class MainMenu : public Gui
{
public:
	MainMenu();
	~MainMenu();
	void hide();
	void show();
	void load(CEGUI::Window* window);
	std::string getUsername();
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