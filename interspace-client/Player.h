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
	StatSet* getStatSet();
	std::string getClass();
	void takeDamage(int damage);
	bool checkDeath();
	void selectClass(std::string className);
	void addExp(int toAdd);
	int getLevel();
	int getExp();
	static int calculateLevel(int xp);
	static int calculateExp(int lev);
private:
	int level, exp, statpoints;
	std::string charClass;
	StatSet* statSet;
};

#endif