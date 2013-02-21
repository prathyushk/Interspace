#include "Enemy.h"
#include <btBulletDynamicsCommon.h>
#include "PhysicsManager.h"
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <boost/thread/mutex.hpp>
#include <SimpleMutex.h>
#include "Client.h"

Enemy::Enemy(int inputDamage, int inputFov, int inputMaxhealth, int inputIndex, btConvexShape* shape, btTransform& transform, PhysicsManager* phys)
	: maxHealth(inputMaxhealth), health(inputMaxhealth), damage(inputDamage), fov(inputFov), index(inputIndex), spawn(transform.getOrigin())
{
	control = phys->addCharacterControl(transform, shape, 0.05f);
	target = NULL;
}

btVector3 Enemy::getPosition()
{
	return control->getGhostObject()->getWorldTransform().getOrigin();
}

btVector3 Enemy::getDirection()
{
	return direction;
}

btKinematicCharacterController* Enemy::getControl()
{
	return control;
}

int Enemy::getDamage()
{
  return damage;
}

int Enemy::getHealth()
{
  return health;
}

void Enemy::takeDamage(int damage)
{
	health -= damage;
	if(health <= 0)
	{
		control->getGhostObject()->getWorldTransform().setOrigin(spawn);
		health = maxHealth;
	}
}

void Enemy::setTarget(Client* client)
{
	target = client;
}

Client* Enemy::getTarget()
{
	return target;
}

int Enemy::getFov()
{
	return fov;
}

void Enemy::setWalkDirection(const btVector3& dir)
{
	walkDirection = dir;
}

void Enemy::update()
{
	try{
		if(target == NULL)
		{
			control->setWalkDirection(walkDirection);
			direction = walkDirection;
		}
		else
		{
			btVector3 temp = target->getPos() - getPosition();
			direction = btVector3(temp.x(), 0, temp.z());
			if(getPosition().distance(target->getPos()) <= 40)
				control->setWalkDirection(btVector3(0,0,0));
			else
				control->setWalkDirection(btVector3(direction.x() / 250,0,direction.z()/250));
		}
	}
	catch(int e){}
}
