#include "MainMenu.h"
#include <CEGUI.h>
#include "Interspace.h"
#include <Ogre.h>
#include <CEGUIString.h>

MainMenu::MainMenu()
	:Gui("MainMenu")
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

void MainMenu::load(CEGUI::Window* window)
{
	mWinMgr = CEGUI::WindowManager::getSingletonPtr();
	mSystem = CEGUI::System::getSingletonPtr();
	mWindow = window;
	engine = Interspace::getSingletonPtr();
	guiLayout = mWinMgr->loadWindowLayout("MainMenu.layout");
	mWindow->addChildWindow(guiLayout);
	CEGUI::Editbox* box = static_cast<CEGUI::Editbox*>(mWinMgr->getWindow("/Login/Password"));
	box->setTextMasked(true);
	mWinMgr->getWindow("/Start")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::startButtonClicked, this));
	mWinMgr->getWindow("/Options")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::optionsButtonClicked, this));
	mWinMgr->getWindow("/Credits")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::creditsButtonClicked, this));
	mWinMgr->getWindow("/Login/Go")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::goButtonClicked, this));
	mWinMgr->getWindow("/Tutorial?/Yes")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::yesTutorial, this));
	mWinMgr->getWindow("/Tutorial?/No")->subscribeEvent(CEGUI::PushButton::EventMouseButtonUp, CEGUI::Event::Subscriber(&MainMenu::noTutorial, this));
	mWinMgr->getWindow("/OptionsWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&MainMenu::closeOptions, this));
	mWinMgr->getWindow("/Login")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&MainMenu::closeLogin, this));
}

std::string MainMenu::getUsername()
{
	return mWinMgr->getWindow("/Login/Username")->getText().c_str();
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