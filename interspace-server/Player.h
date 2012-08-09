#ifndef __Player_h__
#define __Player_h__

#include "Person.h"
#include <Ogre.h>
#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>
#include <string>

class Player : public Person
{
public:
	Player(Ogre::Camera* cam, Ogre::SceneNode* node, Ogre::Vector3 spawn, btConvexShape* shape, PhysicsManager* physics);
	Player(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, PhysicsManager* physics,float stepHeight);
	~Player(void);
private:
	int level, exp, statpoints, health;
	std::string charClass;

};

#endif