#ifndef __Projectile_h__
#define __Projectile_h__

#include <Ogre.h>

class Projectile
{
public:
	Projectile(Ogre::BillboardChain* bbcIn, int index, Ogre::Vector3 start, Ogre::Vector3 stop);
	virtual bool update(double dt) = 0;
protected:
	int myIndex;
	double elapsed;
	Ogre::BillboardChain* bbc;
	Ogre::BillboardChain::Element head;
	Ogre::BillboardChain::Element tail;
	Ogre::SceneManager* sceneMgr;
	Ogre::Vector3 begin;
	Ogre::Vector3 end;
};

#endif