#ifndef __Laser_h__
#define __Laser_h__

#include <Ogre.h>
#include "Projectile.h"

class Laser : public Projectile
{
public:
	Laser(Ogre::BillboardChain* bbc, int index, Ogre::Vector3 start, Ogre::Vector3 end);
	bool update(double dt);
	~Laser();
};

#endif