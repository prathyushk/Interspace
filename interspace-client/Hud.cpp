#include "Hud.h"
#include <CEGUI.h>
#include "Interspace.h"
#include "InputManager.h"
#include "Client.h"
#include <boost/thread/thread.hpp>
#include "Classes.h"
#include "Player.h"
#include "StatSet.h"

Hud::Hud()
	:Gui("Hud"), numThreads(0)
{
}

Hud::~Hud()
{
}

void Hud::load(CEGUI::Window* window)
{
	mWinMgr = CEGUI::WindowManager::getSingletonPtr();
	mSystem = CEGUI::System::getSingletonPtr();
	mWindow = window;
	engine = Interspace::getSingletonPtr();
	guiLayout = mWinMgr->loadWindowLayout("HUD.layout");
	mWindow->addChildWindow(guiLayout);
	CEGUI::Window* chatBox = mWinMgr->getWindow("/ChatBox");
	static_cast<CEGUI::ProgressBar*>(mWinMgr->getWindow("/HUDStats/Healthbar"))->setProgress(1);
	CEGUI::Window* chatHistory = mWinMgr->getWindow("/ChatBox/ChatHistory");
	CEGUI::Window* chatText = mWinMgr->getWindow("/ChatBox/ChatText");
	mWinMgr->getWindow("/ClassSelection/Acrobat")->subscribeEvent(CEGUI::ButtonBase::EventMouseClick, CEGUI::Event::Subscriber(&Hud::acrobatSelected, this));
	mWinMgr->getWindow("/ClassSelection/Juggernaut")->subscribeEvent(CEGUI::ButtonBase::EventMouseClick, CEGUI::Event::Subscriber(&Hud::juggernautSelected, this));
	mWinMgr->getWindow("/ClassSelection/Sniper")->subscribeEvent(CEGUI::ButtonBase::EventMouseClick, CEGUI::Event::Subscriber(&Hud::sniperSelected, this));
	mWinMgr->getWindow("/ClassSelection")->setVisible(true);
	chatBox->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&Hud::chatBoxClosed, this));
	chatText->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&Hud::sendChat, this));
}

void Hud::openChatBox()
{
	mWinMgr->getWindow("/ChatBox")->show();
	mWinMgr->getWindow("/ChatBox/ChatText")->activate();
}

void Hud::closeChatBox()
{
	CEGUI::Editbox* chatText = static_cast<CEGUI::Editbox*>(mWinMgr->getWindow("/ChatBox/ChatText"));
	chatText->setText("");
	mWinMgr->getWindow("/ChatBox/ChatText")->deactivate();
	mWinMgr->getWindow("/ChatBox")->hide();
}

bool Hud::isChatBoxOpen()
{
	return mWinMgr->getWindow("/ChatBox")->isVisible();
}

bool Hud::acrobatSelected(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ClassSelection")->hide();
	engine->getPlayer()->setClass(Classes::ACROBAT);
	return true;
}

bool Hud::juggernautSelected(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ClassSelection")->hide();
	engine->getPlayer()->setClass(Classes::JUGGERNAUT);
	return true;
}

bool Hud::sniperSelected(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ClassSelection")->hide();
	engine->getPlayer()->setClass(Classes::SNIPER);
	return true;
}

bool Hud::chatBoxClosed(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ChatBox")->hide();
	return true;
}

int Hud::chatBoxAppear()
{
	numThreads++;
	mWinMgr->getWindow("/ChatBox")->setVisible(true);
	boost::this_thread::sleep(boost::posix_time::seconds(3));
	if(numThreads == 1 && !CEGUI::MouseCursor::getSingleton().isVisible() && !mWinMgr->getWindow("/ChatBox/ChatText")->isActive())
		mWinMgr->getWindow("/ChatBox")->setVisible(false);
	numThreads--;
	return 0;
}

void Hud::update(Player* player)
{
	mWinMgr->getWindow("/HUDStats/Health")->setText("Health: " + std::to_string(static_cast<long long>(player->getHealth())) + "/" + std::to_string(static_cast<long double>(player->getStatSet()->getMaxHealth())));
	CEGUI::ProgressBar* healthBar = static_cast<CEGUI::ProgressBar*>(mWinMgr->getWindow("/HUDStats/Healthbar"));
	healthBar->setProgress(player->getHealth()/player->getStatSet()->getMaxHealth());
	mWinMgr->getWindow("/HUDStats/Playername")->setText("Name: " + player->getName());
	mWinMgr->getWindow("/HUDStats/Class")->setText("Class: " + player->getClass());
}

bool Hud::sendChat(const CEGUI::EventArgs& args)
{
	CEGUI::Editbox* chatText = static_cast<CEGUI::Editbox*>(mWinMgr->getWindow("/ChatBox/ChatText"));
	CEGUI::String text = chatText->getText();
	if(text.compare("") != 0)
	{
		engine->getClient()->sendMessage(engine->getPlayer()->getName() + ": " + text.c_str());
		chatText->setText("");
		chatText->deactivate();	
	}
	return true;
}

void Hud::addToChat(std::string str)
{
	CEGUI::ListboxItem* chatItem = new CEGUI::ListboxTextItem(str);
	CEGUI::Listbox* listbox = static_cast<CEGUI::Listbox*>(mWinMgr->getWindow("/ChatBox/ChatHistory"));
	listbox->addItem(chatItem);
	listbox->ensureItemIsVisible(chatItem);
	boost::thread thr(boost::bind(&Hud::chatBoxAppear,this));
}

void Hud::hide()
{
	CEGUI::MouseCursor::getSingleton().hide();
	mWinMgr->getWindow("/ChatBox")->hide();
	static_cast<CEGUI::Editbox*>(mWinMgr->getWindow("/ChatBox/ChatText"))->deactivate();
}

void Hud::show()
{
	CEGUI::MouseCursor::getSingleton().show();
	mWinMgr->getWindow("/ChatBox")->show();
}