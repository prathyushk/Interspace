#include "Player.h"
#include <Ogre.h>
#include "PhysicsManager.h"

Player::Player(Ogre::Camera* cam, Ogre::SceneNode* node, Ogre::Vector3 pos, btConvexShape* shape, PhysicsManager* phys)
	:Person(cam,node,pos,shape,phys)
{
}

Player::Player(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, PhysicsManager* physics,float stepHeight)
	:Person(entity,node,name,position,shape,physics,stepHeight)
{
}

Player::~Player()
{
}