#ifndef __Game_h_
#define __Game_h_

class InputHandler;
class Client;
class MainMenu;
class Gui;
#include <OgreWindowEventUtilities.h>
#include <vector>
#include <OIS.h>
#include <OgreRoot.h>
#include "PhysicsManager.h"
#include <OISMouse.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include "BtOgreExtras.h"
#include "Person.h"
#include "Player.h"
#include "Euler.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "Hud.h"
#include "AudioManager.h"
#include "CmdLineConfig.h"

class Game
{
public:
	Game(
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	     CmdLineConfig
#endif
	     );
	virtual ~Game(void);
	bool start(void);
	bool go(void);
	void updatePhysics(double dt);
	void update(double dt);
	Ogre::Camera* getCamera(void);
	void injectKeyPressed(OIS::KeyCode key);
	void injectKeyReleased(OIS::KeyCode key);
	void injectGuiKeyPressed(OIS::KeyCode key);
	void injectMouseMoved(float dx,float dy);
	void injectMousePressed(OIS::MouseButtonID id);
	void injectMouseReleased(OIS::MouseButtonID id);
	int getIndex(void);
	void setIndex(int index);
	Gui* getGui(void);
	std::vector<Player*>* getPlayers(void);
	std::vector<Person*>* getEnemies(void);
	Ogre::SceneManager* getSceneManager(void);
	PhysicsManager* getPhysicsManager(void);
	Ogre::RaySceneQuery* getRaySceneQuery(void);
	void createPlayer(int index);
private:
	Gui* gui;
	AudioManager* audioManager;
	Ogre::Euler camEuler;
	std::vector<Player*>* players;
	std::vector<Person*>* enemies;
	Client* client;
	Ogre::RaySceneQuery* mRaySceneQuery;
	Ogre::Root* mRoot;
	Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	PhysicsManager* phys;
	Player* player;
	btKinematicCharacterController* enemy;
	BtOgre::DebugDrawer* debug;
	int forward, backward, left, right, myIndex;
	InputHandler* input;
	void initCamera(void);
	void createScene(void);
	void camMove(void);
	void loadResouces(void);
	void createEnemies(void);
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	CmdLineConfig config;
#endif
};

#endif
