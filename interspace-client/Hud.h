#ifndef __Hud_h_
#define __Hud_h_

class Client;
class Interspace;
#include <CEGUI.h>
#include <string>
#include "Gui.h"
#include "Player.h"

class Hud : public Gui
{
public:
	Hud();
	~Hud();
	void hide();
	void show();
	void load(CEGUI::Window* window);
	void openChatBox();
	void closeChatBox();
	bool isChatBoxOpen();
	void addToChat(std::string str);
	void update(Player* player);
private:
	int numThreads;
	int chatBoxAppear();
	bool chatBoxClosed(const CEGUI::EventArgs&);
	bool sendChat(const CEGUI::EventArgs&);
	bool acrobatSelected(const CEGUI::EventArgs&);
	bool juggernautSelected(const CEGUI::EventArgs&);
	bool sniperSelected(const CEGUI::EventArgs&);
};

#endif