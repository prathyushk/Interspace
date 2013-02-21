#ifndef __Enemy_h_
#define __Enemy_h_

#include <btBulletDynamicsCommon.h>
#include "PhysicsManager.h"
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include "Client.h"

class Enemy
{
public:
	Enemy(int damage, int fov, int maxhealth, int index, btConvexShape* shape, btTransform& transform, PhysicsManager* phys);
	~Enemy();
	btVector3 getPosition(void);
	btVector3 getDirection(void);
	btKinematicCharacterController* getControl(void);
	Client* getTarget(void);
	int getDamage();
	void takeDamage(int damage);
	int getFov(void);
	void setTarget(Client* client);
	void update(void);
	void setWalkDirection(const btVector3& dir);
	int getHealth();
private:
	int maxHealth, health, damage, fov, index;
	btVector3 spawn;
	btVector3 direction;
	btVector3 walkDirection;
	Client* target;
	btKinematicCharacterController* control;
};

#endif
