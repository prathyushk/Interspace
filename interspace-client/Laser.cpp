#include "Laser.h"
#include "Projectile.h"
#include <Ogre.h>

Laser::Laser(Ogre::BillboardChain* bbcIn, int index, Ogre::Vector3 start, Ogre::Vector3 end)
	:Projectile(bbcIn,index,start,end)
{
	head = Ogre::BillboardChain::Element(start,0.1,0,Ogre::ColourValue(1,0,0,0.5),Ogre::Quaternion(0,0,0,0));
	tail = Ogre::BillboardChain::Element(end,0.1,0,Ogre::ColourValue(1,0,0,0.5),Ogre::Quaternion(0,0,0,0));
	bbc->addChainElement(myIndex,head);
	bbc->addChainElement(myIndex,tail);
}

Laser::~Laser()
{
}

bool Laser::update(double dt)
{
	elapsed += dt;
	if(elapsed >= 0.1)
	{
		bbc->clearChain(myIndex);
		return true;
	}
	return false;
}