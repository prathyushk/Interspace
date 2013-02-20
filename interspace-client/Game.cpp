#include "Game.h"
#include "PhysicsManager.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "InputManager.h"
#include <boost/thread/thread.hpp>
#include "GlowMaterialListener.h"

Game::Game(
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
   CmdLineConfig inputConfig
#endif
	)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	config = inputConfig;
#endif
}

Game::~Game()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, mInputManager);
	if(mInputManager)
		delete mInputManager;
	if(mRoot)
		delete mRoot;
	if(mPhysics)
		delete mPhysics;
}

void Game::updatePhysics(double dt)
{
	mPhysics->update(dt);
}

void Game::loadResources()
{
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}

void Game::initCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setNearClipDistance(5);
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Player");
	node->setOrientation(mCamera->getOrientation());
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	Ogre::CompositorManager::getSingleton().addCompositor(mCamera->getViewport(), "Glow");
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mCamera->getViewport(), "Glow", true);
	GlowMaterialListener *gml = new GlowMaterialListener();
	Ogre::MaterialManager::getSingleton().addListener(gml);
}

void Game::initWindow()
{
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
	mWindow = mRoot->createRenderWindow("Interspace", config.getScreenWidth(), config.getScreenHeight(), config.getFullscreen(), &misc);
#endif
}

void Game::start()
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
	initWindow();
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
	mPhysics = new PhysicsManager();
	initCamera();
	CEGUI::OgreRenderer* renderer = &CEGUI::OgreRenderer::bootstrapSystem(*mWindow);
	mInputManager = new InputManager(mWindow, this);
	mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
	mSoundManager->init();
	init();
	mRoot->addFrameListener(mInputManager);
	mRoot->startRendering();
}

InputManager* Game::getInputManager()
{
	return mInputManager;
}

Ogre::Camera* Game::getCamera()
{
	return mCamera;
}

Ogre::SceneManager* Game::getSceneManager()
{
	return mSceneMgr;
}

Ogre::RenderWindow* Game::getRenderWindow()
{
	return mWindow;
}

PhysicsManager* Game::getPhysicsManager()
{
	return mPhysics;
}

void Game::_update(double dt)
{
	mSoundManager->update(dt);
	mPhysics->update(dt);
	update(dt);
}