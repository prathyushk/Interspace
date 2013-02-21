#ifndef __Person_h_
#define __Person_h_

#include <Ogre.h>
#include <OgreVector3.h>
#include <BulletCollision/CollisionShapes/btConvexShape.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include "PhysicsManager.h"
#include <string>
#include "MovableText.h"

class Person
{
public:
	Person(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, float stepHeight);
	Person(Ogre::Camera* ent, Ogre::SceneNode* model, std::string name, Ogre::Vector3 spawn, btConvexShape* shape);
	virtual ~Person(void);
	btKinematicCharacterController* getControl(void);
	Ogre::SceneNode* getNode(void);
	void setOrientation(Ogre::Quaternion);
	void setPosition(Ogre::Vector3);
	void setDirection(Ogre::Vector3);
	Ogre::Vector3 getPosition();
	void changeName(std::string newName);
	std::string getName();
	Ogre::MovableText* getLabel(void);
	int getHealth();
	void setHealth(int inHealth);
protected:
	Ogre::Vector3 spawnpoint;
	int health;
	std::string myName;
	btKinematicCharacterController* control;
	Ogre::MovableText* label;
};

#endif
