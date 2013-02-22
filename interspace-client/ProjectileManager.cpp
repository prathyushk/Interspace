#include "ProjectileManager.h"
#include <time.h>
#include "Laser.h"
#include "Interspace.h"

template<> ProjectileManager* Ogre::Singleton<ProjectileManager>::msSingleton = 0;

ProjectileManager::ProjectileManager()
	:bbc(0)
{
	Ogre::SceneManager* scenemgr = Interspace::getSingletonPtr()->getSceneManager();
	scenemgr->getRootSceneNode()->createChild("Projectiles");
	bbc = scenemgr->createBillboardChain("lasers");
	scenemgr->getSceneNode("Projectiles")->attachObject(bbc);
	bbc->setMaxChainElements(2);
	bbc->setNumberOfChains(1000);
	bbc->setMaterialName("laser");
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::update(double dt)
{
	for(int i = 0; i < projectiles.size(); i++)
	{
		Projectile* proj = projectiles[i];
		if(proj->update(dt))
		{
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}
}

void ProjectileManager::createLaser(Ogre::SceneManager* scenemgr, Ogre::Vector3 start, Ogre::Vector3 stop)
{
	projectiles.push_back(new Laser(bbc,projectiles.size(),start,stop));
}