#include "Person.h"
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <btBulletDynamicsCommon.h>
#include "PhysicsManager.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "PhysicsManager.h"
#include <OgreCamera.h>
#include "MovableText.h"


Person::Person(Ogre::Entity* ent, Ogre::SceneNode* model, std::string name, Ogre::Vector3 spawn, btConvexShape* shape, float scale)
	:myName(name)
{
	model->attachObject(ent);
	model->setPosition(spawn);
	model->setScale(scale,scale,scale);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(PhysicsManager::convert(spawn));
	control = PhysicsManager::getSingletonPtr()->addCharacterControl(transform, shape, 0.05f, model);
	Ogre::SceneNode* captionNode = model->createChildSceneNode(Ogre::Vector3(0, ent->getBoundingBox().getMaximum().y, 0));
	label = new Ogre::MovableText(name,name,"ArialBlack-8");
	label->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE);
	captionNode->attachObject(label);
	
}

Person::Person(Ogre::Camera* ent, Ogre::SceneNode* model, std::string name, Ogre::Vector3 spawn, btConvexShape* shape)
	:myName(name)
{
	model->attachObject(ent);
	Ogre::Vector3 nodePos = model->getPosition();
	nodePos.y += 20;
	ent->setPosition(nodePos);
	model->setPosition(spawn);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(PhysicsManager::convert(spawn));
	control = PhysicsManager::getSingletonPtr()->addCharacterControl(transform, shape, 0.05f, model);
}

Person::~Person(void)
{
	delete label;
	getNode()->setVisible(false);
}

void Person::changeName(std::string newName)
{
	myName = newName;
	label->setCaption(newName);
}

Ogre::MovableText* Person::getLabel()
{
	return label;
}

btKinematicCharacterController* Person::getControl()
{
	return control;
}

Ogre::SceneNode* Person::getNode()
{
	return static_cast<Ogre::SceneNode *>((control->getGhostObject())->getUserPointer());
}

std::string Person::getName()
{
	return myName;
}

void Person::setPosition(Ogre::Vector3 vec)
{
	control->getGhostObject()->getWorldTransform().setOrigin(PhysicsManager::convert(vec));
}

void Person::setOrientation(Ogre::Quaternion quat)
{
	getNode()->setOrientation(quat);
}

void Person::setDirection(Ogre::Vector3 vec)
{
	getNode()->setDirection(vec);
}

Ogre::Vector3 Person::getPosition()
{
	return getNode()->getPosition();
}