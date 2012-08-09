#ifndef __Person_h__
#define __Person_h__

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
	Person(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, PhysicsManager* physics,float stepHeight);
	Person(Ogre::Camera* ent, Ogre::SceneNode* model, Ogre::Vector3 spawn, btConvexShape* shape, PhysicsManager* phys);
	virtual ~Person(void);
	btKinematicCharacterController* getControl(void);
	Ogre::SceneNode* getNode(void);
	void setOrientation(Ogre::Quaternion);
	void setPosition(Ogre::Vector3);
	void setDirection(Ogre::Vector3);
	Ogre::MovableText* getLabel(void);
protected:
	btKinematicCharacterController* control;
	Ogre::MovableText* label;
};

#endif
