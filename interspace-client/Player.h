#ifndef __Player_h_
#define __Player_h_

#include "Person.h"
#include <Ogre.h>
#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>
#include <string>
#include "StatSet.h"

class Player : public Person
{
public:
	Player(Ogre::Camera* cam, Ogre::SceneNode* node, std::string name, Ogre::Vector3 spawn, btConvexShape* shape);
	Player(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, float stepHeight);
	~Player(void);
	void setClass(std::string className);
	int getHealth();
	StatSet* getStatSet();
	std::string getClass();
	void takeDamage(int damage);
	bool checkDeath();
	void selectClass(std::string className);
private:
	int level, exp, statpoints, health;
	std::string charClass;
	StatSet* statSet;
};

#endif