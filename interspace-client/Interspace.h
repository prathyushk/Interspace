#ifndef __Interspace_h__
#define __Interspace_h__

class GuiManager;
class InputHandler;
class Client;
class MainMenu;
class Hud;
#include "Game.h"
#include <Ogre.h>
#include "AudioManager.h"
#include "Euler.h"
#include "Player.h"
#include <vector>
#include "BtOgreExtras.h"
#include "BtOgreGP.h"
#include "BtOgrePG.h"

class Interspace : public Game, public Ogre::Singleton<Interspace>
{
public:
	Interspace(
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
		CmdLineConfig inputConfig
#endif
		);
	~Interspace();
	void exitMenu();
	GuiManager* getGuiManager();
	Ogre::Euler* getCamEuler();
	AudioManager* getAudioManager();
	Client* getClient();
	void setForward(bool set);
	void setBackward(bool set);
	void setLeft(bool set);
	void setRight(bool set);
	Player* getPlayer();
	std::vector<Person*>* getEnemies();
	std::vector<Person*>* getPlayers();
	int getIndex();
	void setIndex(int index);
private:
	BtOgre::DebugDrawer* mDebugDrawer;
	AudioManager* mAudioManager;
	GuiManager* mGuiManager;
	Ogre::Euler* camEuler;
	Client* client;
	std::vector<Person*>* enemies;
	std::vector<Person*>* players;
	Player* player;
	void update(double dt);
	int init();
	void camMove();
	void initScene(std::string charName);
	int myIndex;
	bool forward, backward, right, left;
};

#endif