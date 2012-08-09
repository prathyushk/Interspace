#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <OgreSceneManager.h>
#include "BtOgreExtras.h"
#include "OgreMotionState.h"
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <vector>

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

btKinematicCharacterController* PhysicsManager::addCharacterControl(btTransform& trans, btConvexShape* shape, float stepHeight, Ogre::SceneNode* node)
{
	btPairCachingGhostObject* ghost = new btPairCachingGhostObject();
	ghost->setWorldTransform(trans);
	ghost->setCollisionShape(shape);
	ghost->setUserPointer(node);
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
	btKinematicCharacterController* control;
	for(std::vector<btKinematicCharacterController*>::iterator it = characterControls.begin(); it != characterControls.end(); ++it)
	{
		control = *it;
		Ogre::SceneNode* node = static_cast<Ogre::SceneNode *>((control->getGhostObject())->getUserPointer());
		btVector3 pos = control->getGhostObject()->getWorldTransform().getOrigin();
		node->setPosition(pos.x(),pos.y(),pos.z());
	}
}

btRigidBody* PhysicsManager::addRigidBody(btTransform& trans,btCollisionShape* shape, float mass,Ogre::SceneNode* node)
{
	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);
	OgreMotionState * motionState = new OgreMotionState(trans, node);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
	btRigidBody * body = new btRigidBody(rbInfo);
	world->addRigidBody(body);
	return body;
}

btVector3 PhysicsManager::vec3OgreToBullet(const Ogre::Vector3& vec)
{
	return btVector3(vec.x, vec.y, vec.z);
}

btQuaternion PhysicsManager::quatOgreToBullet(const Ogre::Quaternion& quat)
{
	return btQuaternion(quat.w, quat.x, quat.y, quat.z);
}

Ogre::Vector3 PhysicsManager::vec3BulletToOgre(const btVector3& vec)
{
	return Ogre::Vector3(vec.x(),vec.y(),vec.z());
}

Ogre::Quaternion PhysicsManager::quatBulletToOgre(const btQuaternion& quat)
{
	return Ogre::Quaternion(quat.w(), quat.x(), quat.y(), quat.z());
}

btDynamicsWorld* PhysicsManager::getWorld()
{
	return world;
}