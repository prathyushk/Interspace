#ifndef __Enemy_h__
#define __Enemy_h__

#include "Person.h"
#include <Ogre.h>
#include "Player.h"

class Enemy : public Person
{
public:
	Enemy(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, float stepHeight, int xp);
	~Enemy();
	void checkDeath(Player* player);
protected:
	int exp;
};

#endif