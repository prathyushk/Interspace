#ifndef __PhysicsManager_h_
#define __PhysicsManager_h_

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <vector>

class PhysicsManager
{
public:
	PhysicsManager(void);
	~PhysicsManager(void);
	void addToWorld(btRigidBody*);
	btDynamicsWorld* getWorld(void);
	void update(double);
	btRigidBody* addRigidBody(btTransform&,btCollisionShape*,float);
	btKinematicCharacterController* addCharacterControl(btTransform&,btConvexShape*,float);
private:
	std::vector<btKinematicCharacterController*> characterControls;
	btDiscreteDynamicsWorld* world;
	btBroadphaseInterface* broadPhase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
};

#endif
