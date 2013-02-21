#include "Robo.h"
#include <Ogre.h>
#include "Interspace.h"

Robo::Robo(Ogre::SceneNode* attach, int index)
	:Enemy(Interspace::getSingletonPtr()->getSceneManager()->createEntity("enemyEnt_" + std::to_string(static_cast<long long>(index)), "robo.mesh"),
		attach,"Robo",Ogre::Vector3(0,50,-30 - (index*20)),new btCapsuleShape(5,15), 5, 2)
{
}