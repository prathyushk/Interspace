#include "Projectile.h"
#include <Ogre.h>

Projectile::Projectile(Ogre::BillboardChain* bbcIn, int index,Ogre::Vector3 start, Ogre::Vector3 stop)
	:elapsed(0), bbc(bbcIn), myIndex(index),begin(start),end(stop)
{
}