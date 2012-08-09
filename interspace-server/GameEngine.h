#ifndef __GameEngine_h__
#define __GameEngine_h__

#include <Ogre.h>
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "InputHandler.h"
#include "GuiManager.h"
#include "Client.h"
#include "Player.h"
#include <string>

class GameEngine
{
public:
	GameEngine(std::string title);
	~GameEngine();
	Ogre::RenderWindow* getRenderWindow();
private:
	void initCamera();
	void createScene();
	void camMove();
	void loadResouces();
	void createEnemies();
	void createWindow();
	Ogre::Camera* mCamera;
	Ogre::Euler camEuler;
	Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	InputHandler* input;
	AudioManager* audioManager;
	PhysicsManager* phys;
	GuiManager* guiManager;
	Client* client;
	Player* player;
};

#endif