#include "Enemy.h"
#include <Ogre.h>
#include "Player.h"

Enemy::Enemy(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, float stepHeight, int xp)
	:Person(entity,node,name,position,shape,stepHeight), exp(xp)
{
	label->setColor(Ogre::ColourValue::Red);
}

Enemy::~Enemy()
{
}

void Enemy::checkDeath(Player* player)
{
	if(health <= 0)
	{
		player->addExp(exp);
	}
}