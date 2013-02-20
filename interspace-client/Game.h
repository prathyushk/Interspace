#ifndef __Game_h__
#define __Game_h__

class InputManager;
#include <Ogre.h>
#include <OgreOggSound.h>
#include "PhysicsManager.h"
#include "Euler.h"

class Game
{
public:
	Game(
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
		CmdLineConfig
#endif
		);
	virtual ~Game();
	virtual void start();
	void updatePhysics(double dt);
	void _update(double dt);
	InputManager* getInputManager();
	Ogre::RenderWindow* getRenderWindow();
	Ogre::Camera* getCamera();
	Ogre::SceneManager* getSceneManager();
	PhysicsManager* getPhysicsManager();
protected:
	OgreOggSound::OgreOggSoundManager* mSoundManager;
	Ogre::Root* mRoot;
	Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	PhysicsManager* mPhysics;
	InputManager* mInputManager;
	virtual void update(double dt)=0;
	virtual int init()=0;
private:
	void windowResized(Ogre::RenderWindow* rw);
	void windowClosed(Ogre::RenderWindow* rw);
	void loadResources();
	void initWindow();
	void initCamera();
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	CmdLineConfig config;
#endif
};

#endif