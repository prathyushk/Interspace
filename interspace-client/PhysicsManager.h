#ifndef __PhysicsManager_h_
#define __PhysicsManager_h_

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <Ogre.h>
#include <vector>

class PhysicsManager : public Ogre::Singleton<PhysicsManager>
{
public:
	PhysicsManager(void);
	~PhysicsManager(void);
	void addToWorld(btRigidBody*);
	btDynamicsWorld* getWorld(void);
	void update(double);
	btRigidBody* addRigidBody(btTransform& transform,btCollisionShape* shape,float mass,Ogre::SceneNode* node);
	btKinematicCharacterController* addCharacterControl(btTransform& transform,btConvexShape* shape,float stepHeight,Ogre::SceneNode* node);
	static btVector3 convert(const Ogre::Vector3& vector); 
	static btQuaternion convert(const Ogre::Quaternion& quaternion);
	static Ogre::Vector3 convert(const btVector3& vector);
	static Ogre::Quaternion convert(const btQuaternion& quaternion);
private:
	std::vector<btKinematicCharacterController*> characterControls;
	btDiscreteDynamicsWorld* world;
	btBroadphaseInterface* broadPhase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
};

#endif
