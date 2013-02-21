#ifndef __Robo_h__
#define __Robo_h__

#include "Enemy.h"
#include <Ogre.h>

class Robo : public Enemy
{
public:
	Robo(Ogre::SceneNode* attach, int index);
};

#endif