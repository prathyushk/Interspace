#ifndef __ProjectileManager_h__
#define __ProjectileManager_h__

#include <vector>
#include <Ogre.h>
#include "Projectile.h"
#include <boost/thread/thread.hpp>

class ProjectileManager : public Ogre::Singleton<ProjectileManager>
{
public:
	ProjectileManager();
	~ProjectileManager();
	void createLaser(Ogre::SceneManager* scenemgr, Ogre::Vector3 start, Ogre::Vector3 end);
	void update(double dt);
private:
	std::vector<Projectile*> projectiles;
	Ogre::BillboardChain* bbc;
};

#endif