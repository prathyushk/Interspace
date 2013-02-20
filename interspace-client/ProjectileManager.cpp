#include "ProjectileManager.h"
#include <time.h>
#include "Laser.h"

template<> ProjectileManager* Ogre::Singleton<ProjectileManager>::msSingleton = 0;

ProjectileManager::ProjectileManager()
	:bbc(0)
{
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
	
	try
	{
		scenemgr->getSceneNode("Projectiles");
	}
	catch(Ogre::Exception e)
	{
		scenemgr->getRootSceneNode()->createChild("Projectiles");
	}
	if(!bbc)
	{
		bbc = scenemgr->createBillboardChain("projectiles");
		scenemgr->getSceneNode("Projectiles")->attachObject(bbc);
		bbc->setMaxChainElements(2);
		bbc->setNumberOfChains(1000);
		bbc->setMaterialName("laser");
	}
	projectiles.push_back(new Laser(bbc,projectiles.size(),start,stop));
}