#include "Hud.h"
#include <CEGUI.h>

Hud::Hud(CEGUI::WindowManager* winMgr, CEGUI::System* sys, CEGUI::Window* win)
	: mWinMgr(winMgr), mSystem(sys), mWindow(win), visible(true)
{
	guiLayout2 = mWinMgr->loadWindowLayout("HUD.layout");
	mWindow->addChildWindow(guiLayout2);
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

Hud::~Hud()
{
}

bool Hud::acrobatSelected(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ClassSelection")->hide();
	return true;
}

bool Hud::juggernautSelected(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ClassSelection")->hide();
	return true;
}

bool Hud::sniperSelected(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ClassSelection")->hide();
	return true;
}

bool Hud::chatBoxClosed(const CEGUI::EventArgs& args)
{
	mWinMgr->getWindow("/ChatBox")->hide();
	return true;
}

bool Hud::sendChat(const CEGUI::EventArgs& args)
{
	CEGUI::Editbox* chatText = static_cast<CEGUI::Editbox*>(mWinMgr->getWindow("/ChatBox/ChatText"));
	CEGUI::String text = chatText->getText();
	chatText->setText("");
	chatText->deactivate();
	CEGUI::ListboxItem* chatItem = new CEGUI::ListboxTextItem(text);
	return true;
}

void Hud::hide()
{
	if(visible)
	{
		CEGUI::MouseCursor::getSingleton().hide();
		mWinMgr->getWindow("/ChatBox")->hide();
		static_cast<CEGUI::Editbox*>(mWinMgr->getWindow("/ChatBox/ChatText"))->deactivate();
		visible = false;
	}
}

void Hud::show()
{
	if(!visible)
	{
		CEGUI::MouseCursor::getSingleton().show();
		mWinMgr->getWindow("/ChatBox")->show();
		visible = true;
	}
}

bool Hud::isVisible()
{
	return visible;
}

CEGUI::Window* Hud::getGuiLayout()
{
	return guiLayout2;
}