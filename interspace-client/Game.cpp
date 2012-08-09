#include <cstdlib>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <Ogre.h>
#include "Game.h"
#include "PhysicsManager.h"
#include "OgreMotionState.h"
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "BtOgreGP.h"
#include <BulletDynamics/Dynamics/btActionInterface.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "InputHandler.h"
#include "Person.h"
#include "Client.h"
#include "Euler.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "Hud.h"
#include "MainMenu.h"
#include "Gui.h"
#include "MovableText.h"
#include "Player.h"
#include "CmdLineConfig.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include <windows.h>
#endif

Game::Game(
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	   CmdLineConfig inputConfig
#endif
	   )
	:mRoot(0),  mPluginsCfg(Ogre::StringUtil::BLANK),
	mResourcesCfg(Ogre::StringUtil::BLANK), forward(0), backward(0), left(0), right(0),
	myIndex(-1), gui(NULL), client(NULL)
{
	players = new std::vector<Player*>();
	enemies = new std::vector<Person*>();
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	config = inputConfig;
#endif
}

Game::~Game(void)
{
	if(mRaySceneQuery)
		delete mRaySceneQuery;
	for(int i = 0; i < players->size(); i++)
		delete players->at(i);
	if(client)
		delete client;
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, input);
	if(input)
		delete input;
	if(mRoot){
		delete mRoot;
	}
	if(phys)
		delete phys;
}

void Game::setIndex(int index)
{
	myIndex = index;
}

int Game::getIndex()
{
	return myIndex;
}

void Game::update(double dt)
{
	audioManager->update(dt);
	if(client)
		client->update();
	camMove();
	phys->update(dt);
	debug->step();
}

void Game::updatePhysics(double dt)
{
	phys->update(dt);
}

std::vector<Player*>* Game::getPlayers()
{
	return players;
}

std::vector<Person*>* Game::getEnemies()
{
	return enemies;
}

Ogre::SceneManager* Game::getSceneManager(void)
{
	return mSceneMgr;
}

void Game::injectMouseMoved(float dx, float dy)
{
	camEuler.yaw(Ogre::Radian(-dx * 0.0013)).pitch(Ogre::Radian(-dy * 0.0013)).setRoll(Ogre::Degree(0));
	if(camEuler.getPitch() < Ogre::Degree(-90))
		camEuler.setPitch(Ogre::Degree(-90));
	if(camEuler.getPitch() > Ogre::Degree(90))
		camEuler.setPitch(Ogre::Degree(90));
	mCamera->setOrientation(camEuler);
}

void Game::injectMousePressed(OIS::MouseButtonID button)
{
	if(button == OIS::MB_Left)
	{	
		audioManager->playGunshot();
		Ogre::Ray mouseRay(mCamera->getDerivedPosition(), mCamera->getDerivedDirection());
		mRaySceneQuery->setRay(mouseRay);
		mRaySceneQuery->setSortByDistance(true);
		Ogre::RaySceneQueryResult result = mRaySceneQuery->execute();
		Ogre::RaySceneQueryResult::iterator iter = result.begin();
		if(iter != result.end())
		{
			try
			{
				if(iter->movable->getParentNode()->getName().substr(0,5).compare("enemy") == 0)
				{
					std::string name = iter->movable->getParentNode()->getName();
					client->sendDamage(atoi(name.substr(name.find_first_of('_') + 1, name.size()).c_str()), 20);
				}
			}
			catch(int e){}
		}
	}
}

void Game::injectMouseReleased(OIS::MouseButtonID button)
{
}

void Game::injectKeyPressed(OIS::KeyCode key)
{
	switch(key)
	{
	case OIS::KC_SPACE: player->getControl()->jump(); break;
	case OIS::KC_W: forward = 1; break;
	case OIS::KC_S: backward = 1; break;
	case OIS::KC_A: left = 1; break;
	case OIS::KC_D: right = 1; break;
	}
}

void Game::injectGuiKeyPressed(OIS::KeyCode key)
{
	switch(key)
	{
	case OIS::KC_LCONTROL:
	case OIS::KC_RCONTROL:
		if(gui->isHud()){
			if(gui->isVisible())
				gui->getHud()->hide();
			else
				gui->getHud()->show();
		}
		break;
	}
}

void Game::injectKeyReleased(OIS::KeyCode key)
{
	switch(key)
	{
	case OIS::KC_W: forward = 0; break;
	case OIS::KC_S: backward = 0; break;
	case OIS::KC_A: left = 0; break;
	case OIS::KC_D: right = 0; break;
	}
}

Ogre::Camera* Game::getCamera()
{
	return mCamera;
}

PhysicsManager* Game::getPhysicsManager()
{
	return phys;
}

Ogre::RaySceneQuery* Game::getRaySceneQuery()
{
	return mRaySceneQuery;
}

void Game::camMove()
{
	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	if(forward)
		walkDirection +=  btVector3(mCamera->getDerivedDirection().x,0, mCamera->getDerivedDirection().z);
	if (backward)
		walkDirection -=  btVector3(mCamera->getDerivedDirection().x,0, mCamera->getDerivedDirection().z);
	if(left)
		walkDirection -= btVector3(mCamera->getDerivedRight().x,0,mCamera->getDerivedRight().z);
	if(right)
		walkDirection += btVector3(mCamera->getDerivedRight().x,0,mCamera->getDerivedRight().z);
	player->getControl()->setWalkDirection(walkDirection);
	btVector3 pos = player->getControl()->getGhostObject()->getWorldTransform().getOrigin();
	mSceneMgr->getRootSceneNode()->getChild("Player")->setPosition(pos.x(),pos.y(),pos.z());
	Ogre::Vector3 position = mSceneMgr->getSceneNode("Player")->getPosition();
	if(client)
		client->sendPosition(position, Ogre::Vector3((camEuler.getYaw() + Ogre::Degree(180)).valueDegrees(), 0, camEuler.getRoll().valueDegrees()));
}

void Game::loadResouces()
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
	player = new Player(mCamera, node, Ogre::Vector3(0,10,80), new btCapsuleShape(5,25), phys);
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void Game::createScene()
{
	Ogre::Entity *ent;
	Ogre::Plane p;
	p.normal = Ogre::Vector3(0,1,0); p.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"FloorPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		p, 200000, 200000, 20, 20, true, 1, 9000,9000,Ogre::Vector3::UNIT_Z);
	ent = mSceneMgr->createEntity("floor", "FloorPlane");
	ent->setMaterialName("phong1");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(btVector3(0,0,0));
	btRigidBody *RigidBody = phys->addRigidBody(Transform,new btStaticPlaneShape(btVector3(0,1,0),0),0,node);
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(20,80,50);
}

void Game::createEnemies()
{
	for(int i = 0; i < 10; i++){
		Ogre::Entity* enemyEnt = mSceneMgr->createEntity("enemyEnt_" + std::to_string(static_cast<long long>(i)), "robo.mesh");
		Ogre::SceneNode* enemyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemy_" + std::to_string(static_cast<long long>(i)));
		enemies->push_back(new Person(enemyEnt,enemyNode,"Robo",Ogre::Vector3(0,50,-30 - (i*20)),new btCapsuleShape(5,15),phys, 5));
		enemies->at(enemies->size()-1)->getLabel()->setColor(Ogre::ColourValue::Red);
	}
}


bool Game::start(void)
{
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif
	mRoot = new Ogre::Root(mPluginsCfg);
	loadResouces();
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
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
	phys = new PhysicsManager();
	debug = new BtOgre::DebugDrawer(mSceneMgr->getRootSceneNode(), phys->getWorld());
	//phys->getWorld()->setDebugDrawer(debug);
	initCamera();
	CEGUI::OgreRenderer* renderer = &CEGUI::OgreRenderer::bootstrapSystem(*mWindow);
	input = new InputHandler(mWindow, this);
	gui = new Gui(this);
	mRoot->addFrameListener(input);
	mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
	audioManager = new AudioManager();
	audioManager->playMain();
	mRoot->addFrameListener(input);
	mRoot->startRendering();
	return true;
}

bool Game::go()
{
	gui->openHud();
	gui->getMenu()->setVisible(false);
	createScene();
	createEnemies();
	client = new Client(this);
	while(!client->isConnected())
		client->update();
	return true;
}

Gui* Game::getGui()
{
	return gui;
}
