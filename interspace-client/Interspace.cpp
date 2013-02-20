#include "Interspace.h"
#include "GuiManager.h"
#include "MainMenu.h"
#include "AudioManager.h"
#include <OgreOggSound.h>
#include "Euler.h"
#include "Player.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <btBulletDynamicsCommon.h>
#include "InputManager.h"
#include "InputListener.h"
#include "InputHandler.h"
#include <string>
#include "Client.h"
#include <boost/thread/thread.hpp>
#include "Hud.h"
#include "BtOgreGP.h"
#include "BtOgrePG.h"
#include "ProjectileManager.h"

template<> Interspace* Ogre::Singleton<Interspace>::msSingleton = 0;

Interspace::Interspace(
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
		CmdLineConfig inputConfig
#endif
	)
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	: Game(inputConfig)
#else
	:
#endif
	forward(false), backward(false), left(false), right(false), camEuler(new Ogre::Euler()), mGuiManager(0), player(0), client(0),
	enemies(new std::vector<Person*>()), players(new std::vector<Person*>()), myIndex(-1)
{

}

Interspace::~Interspace()
{
	delete camEuler;
}

void Interspace::update(double dt)
{
	ProjectileManager::getSingleton().update(dt);
	if(player)
	{
		camMove();
		if(player->checkDeath())
			client->sendMessage(player->getName() + " has died");
	}
	if(client)
		client->update();
	Hud* hud = dynamic_cast<Hud*>(mGuiManager->getGui());
	if(hud && player)
		hud->update(player);
	//if(mDebugDrawer)
		//mDebugDrawer->step();
}

int Interspace::init()
{
	new ProjectileManager();
	mGuiManager = new GuiManager();
	mAudioManager = new AudioManager();
	mInputManager->addListener(new InputHandler());
	mAudioManager->playMain();
	mDebugDrawer = new BtOgre::DebugDrawer(mSceneMgr->getRootSceneNode(), mPhysics->getWorld());
	mPhysics->getWorld()->setDebugDrawer(mDebugDrawer);
	return 0;
}

GuiManager* Interspace::getGuiManager()
{
	return mGuiManager;
}

void Interspace::initScene(std::string charName)
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
	btRigidBody *RigidBody = mPhysics->addRigidBody(Transform,new btStaticPlaneShape(btVector3(0,1,0),0),0,node);
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(20,80,50);
	player = new Player(mCamera, mSceneMgr->getSceneNode("Player"), charName, Ogre::Vector3(0,100,80), new btCapsuleShape(5,25));
	for(int i = 0; i < 10; i++){
		Ogre::Entity* enemyEnt = mSceneMgr->createEntity("enemyEnt_" + std::to_string(static_cast<long long>(i)), "robo.mesh");
		Ogre::SceneNode* enemyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemy_" + std::to_string(static_cast<long long>(i)));
		enemies->push_back(new Person(enemyEnt,enemyNode,"Robo",Ogre::Vector3(0,50,-30 - (i*20)),new btCapsuleShape(5,15), 5));
		enemies->at(enemies->size()-1)->getLabel()->setColor(Ogre::ColourValue::Red);
	}
}

void Interspace::camMove()
{
	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	Ogre::Vector3 derivedDirection = mCamera->getDerivedDirection() *  player->getStatSet()->getSpeed();
	Ogre::Vector3 derivedRight = mCamera->getDerivedRight() * player->getStatSet()->getSpeed();
	if(forward)
		walkDirection +=  btVector3(derivedDirection.x,0, derivedDirection.z);
	if (backward)
		walkDirection -=  btVector3(derivedDirection.x,0, derivedDirection.z);
	if(left)
		walkDirection -= btVector3(derivedRight.x * 0.4 * player->getStatSet()->getSpeed(),0,derivedRight.z);
	if(right)
		walkDirection += btVector3(derivedRight.x,0,derivedRight.z);
	player->getControl()->setWalkDirection(walkDirection);
	btVector3 pos = player->getControl()->getGhostObject()->getWorldTransform().getOrigin();
	mSceneMgr->getRootSceneNode()->getChild("Player")->setPosition(pos.x(),pos.y(),pos.z());
	Ogre::Vector3 position = mSceneMgr->getSceneNode("Player")->getPosition();
	if(client)
		client->sendPosition(position, Ogre::Vector3((camEuler->getYaw() + Ogre::Degree(180)).valueDegrees(), 0, camEuler->getRoll().valueDegrees()));
}

void Interspace::exitMenu()
{
	MainMenu* menu = static_cast<MainMenu*>(mGuiManager->getGui());
	std::string username = menu->getUsername();
	mGuiManager->next();
	initScene(username);
	client = new Client();
	while(!client->isConnected())
		client->update();
}

std::vector<Person*>* Interspace::getEnemies()
{
	return enemies;
}

std::vector<Person*>* Interspace::getPlayers()
{
	return players;
}

Ogre::Euler* Interspace::getCamEuler()
{
	return camEuler;
}

AudioManager* Interspace::getAudioManager()
{
	return mAudioManager;
}

Client* Interspace::getClient()
{
	return client;
}

Player* Interspace::getPlayer()
{
	return player;
}

void Interspace::setIndex(int ind)
{
	myIndex = ind;
}

int Interspace::getIndex()
{
	return myIndex;
}

void Interspace::setForward(bool set)
{
	forward = set;
}

void Interspace::setBackward(bool set)
{
	backward = set;
}

void Interspace::setLeft(bool set)
{
	left = set;
}

void Interspace::setRight(bool set)
{
	right = set;
}