#include "GameEngine.h"
#include <string>
#include "InputHandler.h"

GameEngine::GameEngine(std::string name)
{
	#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif
	mRoot = new Ogre::Root(mPluginsCfg);
	loadResources();
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	mRoot->setRenderSystem(mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem"));
#else
	mRoot->setRenderSystem(mRoot->getRenderSystemByName("OpenGL Rendering Subsystem"));
#endif
	mRoot->initialise(false);
	Ogre::NameValuePairList misc;
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
	mWindow = mRoot->createRenderWindow("Interspace", desktop.right, desktop.bottom, false, &misc);
#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	Display *dsp = NULL;
	Screen *scr = NULL;
	dsp = XOpenDisplay(NULL);
	if (! dsp) {
	  std::cerr << "Unable to open display" << std::endl;
	  exit(-1);
	}
	scr = DefaultScreenOfDisplay(dsp);
	if (! scr) {
	  std::cerr << "Unable to open default screen of display" << std::endl;
	  exit(-1);
	}
	mWindow = mRoot->createRenderWindow("Interspace", scr->width, scr->height, true, &misc);
	XCloseDisplay(dsp);
#endif
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
	phys = new PhysicsManager();
	initCamera();
	input = new InputHandler(mWindow, this);
	guiManager = new GuiManager(this);
	//gui = new Gui(this);
	mRoot->addFrameListener(input);
	audioManager = new AudioManager();
	audioManager->playMain();
	mRoot->addFrameListener(input);
	mRoot->startRendering();
}

