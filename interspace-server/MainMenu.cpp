#include "MainMenu.h"
#include <CEGUI.h>
#include "GameEngine.h"
#include <Ogre.h>
#include <CEGUIString.h>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::hide()
{
}

void MainMenu::show()
{
}

void MainMenu::load(CEGUI::WindowManager* winMgr, CEGUI::System* sys, CEGUI::Window* window, GameEngine* eng)
{
	mWinMgr = winMgr;
	mSystem = sys;
	mWindow = window;
	engine = eng;
	guiLayout = mWinMgr->loadWindowLayout("MainMenu.layout");
	mWindow->addChildWindow(guiLayout);
	mWinMgr->getWindow("/Start")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::startButtonClicked, this));
	mWinMgr->getWindow("/Options")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::optionsButtonClicked, this));
	mWinMgr->getWindow("/Credits")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::creditsButtonClicked, this));
	mWinMgr->getWindow("/Login/Go")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::goButtonClicked, this));
	mWinMgr->getWindow("/Tutorial?/Yes")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::yesTutorial, this));
	mWinMgr->getWindow("/Tutorial?/No")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::noTutorial, this));
	mWinMgr->getWindow("/OptionsWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&MainMenu::closeOptions, this));
	mWinMgr->getWindow("/Login")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&MainMenu::closeLogin, this));
}

bool MainMenu::startButtonClicked(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/Login")->setVisible(true);
	mWinMgr->getWindow("/Login")->activate();
	return true;
}

bool MainMenu::optionsButtonClicked(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/OptionsWindow")->setVisible(true);
	mWinMgr->getWindow("/OptionsWindow")->activate();
	return true;
}

bool MainMenu::creditsButtonClicked(const CEGUI::EventArgs& args)
{
	return true;
}

bool MainMenu::goButtonClicked(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/Tutorial?")->setVisible(true);
	mWinMgr->getWindow("/Tutorial?")->activate();
	return true;
}

bool MainMenu::yesTutorial(const CEGUI::EventArgs& args)
{
	engine->exitMenu();
	return true;
}

bool MainMenu::noTutorial(const CEGUI::EventArgs& args)
{
	engine->exitMenu();
	return true;
}

bool MainMenu::closeOptions(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/OptionsWindow")->setVisible(false);
	return true;
}

bool MainMenu::closeLogin(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/Login")->setVisible(false);
	return true;
}