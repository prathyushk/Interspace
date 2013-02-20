#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <vector>
#include <iostream>

PhysicsManager::PhysicsManager(void)
{
	broadPhase = new btDbvtBroadphase();
	broadPhase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);
	world->setGravity(btVector3(0,-9.80665f,0));
}


PhysicsManager::~PhysicsManager(void)
{
	for (int i = world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject * obj = world->getCollisionObjectArray()[i];
		btRigidBody * body = btRigidBody::upcast(obj);

		if (body && body->getMotionState())
			delete body->getMotionState();

		world->removeCollisionObject(obj);

		delete obj;
	}
	for(std::vector<btKinematicCharacterController*>::iterator it = characterControls.begin(); it!= characterControls.end(); ++it)
	{
		delete *it;
	}
	delete world;
	delete solver;
	delete broadPhase;
	delete collisionConfiguration;
}

void PhysicsManager::addToWorld(btRigidBody* body)
{
	world->addRigidBody(body);
}

btKinematicCharacterController* PhysicsManager::addCharacterControl(btTransform& trans, btConvexShape* shape, float stepHeight)
{
	btPairCachingGhostObject* ghost = new btPairCachingGhostObject();
	ghost->setWorldTransform(trans);
	ghost->setCollisionShape(shape);
	btKinematicCharacterController* control = new btKinematicCharacterController(ghost,shape,stepHeight);
	control->setGravity(10);
	control->setFallSpeed(1000);
	control->setJumpSpeed(20);
	world->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
	world->addAction(control);
	characterControls.push_back(control);
	return control;
}

void PhysicsManager::update(double step)
{
	world->stepSimulation(static_cast<btScalar>(step), 60);
}

btRigidBody* PhysicsManager::addRigidBody(btTransform& trans,btCollisionShape* shape, float mass)
{
	btVector3 inertia;
//	shape->calculateLocalInertia(mass, inertia);
	btDefaultMotionState * motionState = new btDefaultMotionState(trans);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
	btRigidBody * body = new btRigidBody(rbInfo);
	world->addRigidBody(body);
	return body;
}

btDynamicsWorld* PhysicsManager::getWorld()
{
	return world;
}
