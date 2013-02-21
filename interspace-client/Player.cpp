#include "Player.h"
#include <Ogre.h>
#include "PhysicsManager.h"
#include <stdlib.h>
#include <time.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <cmath>

Player::Player(Ogre::Camera* cam, Ogre::SceneNode* node, std::string name, Ogre::Vector3 pos, btConvexShape* shape)
	:Person(cam,node,name,pos,shape), exp(0), statpoints(0), level(0)
{
	statSet = new StatSet();
	health = statSet->getMaxHealth();
	control->setJumpSpeed(statSet->getJump());
	charClass = "None";
	srand(time(NULL));
}

Player::Player(Ogre::Entity* entity, Ogre::SceneNode* node, std::string name, Ogre::Vector3 position, btConvexShape* shape, float stepHeight)
	:Person(entity,node,name,position,shape,stepHeight)
{
	PhysicsManager::getSingletonPtr()->getWorld()->removeCharacter(control);
}

Player::~Player()
{
}

int Player::getLevel()
{
	return level;
}

int Player::getExp()
{
	return exp;
}

void Player::addExp(int toAdd)
{
	int prev = level;
	exp += toAdd;
	level = Player::calculateLevel(exp);
	if(prev < level)
		statpoints++;
}

int Player::calculateLevel(int xp)
{
	return ((int) (std::log((double)xp + 1)/std::log(1.8)));
}

int Player::calculateExp(int lev)
{
	return std::ceil(std::pow(1.8,lev) - 1);
}

void Player::takeDamage(int damage)
{
	int random = rand() % ((int) statSet->getDefense()) + 1;
	if(damage - random <= 0) 
		health -= 1;
	else
		health -= damage - random;
}

bool Player::checkDeath()
{
	if(control->getGhostObject()->getWorldTransform().getOrigin().y() <= -50 || health <= 0)
	{
		health = statSet->getMaxHealth();
		setPosition(spawnpoint);
		return true;
	}
	return false;
}

StatSet* Player::getStatSet()
{
	return statSet;
}

std::string Player::getClass()
{
	return charClass;
}

void Player::setClass(std::string className)
{
	delete statSet;
	statSet = new StatSet(className);
	charClass = className;
	control->setJumpSpeed(statSet->getJump());
	health = statSet->getMaxHealth();
}