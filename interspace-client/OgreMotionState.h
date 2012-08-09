#ifndef __OgreMotionState_h_
#define __OgreMotionState_h_

#include <btBulletDynamicsCommon.h>
#include <OgreSceneNode.h>

class OgreMotionState : public btMotionState {
public:
    OgreMotionState(const btTransform&, Ogre::SceneNode*);
    virtual ~OgreMotionState();
    void setNode(Ogre::SceneNode*);
    virtual void getWorldTransform(btTransform&) const;
    virtual void setWorldTransform(const btTransform&);
protected:
    Ogre::SceneNode *mVisibleobj;
    btTransform mPos1;
};

#endif