#include "InputHandler.h"
#include <OIS.h>
#include "InputManager.h"
#include "GuiManager.h"
#include "Gui.h"
#include "Interspace.h"
#include <Ogre.h>
#include <string>
#include "Euler.h"
#include "AudioManager.h"
#include "Client.h"
#include "Hud.h"
#include "Person.h"
#include "ProjectileManager.h"

InputHandler::InputHandler()
	: game(Interspace::getSingletonPtr())
{
	setInject(true);
}

InputHandler::~InputHandler()
{
}

void InputHandler::toggleGui()
{
	if(game->getGuiManager()->getGui()->getName().compare("Hud") == 0)
	{
		if(game->getGuiManager()->isVisible())
		{
			setInject(false);
			game->getGuiManager()->closeGui();
		}
		else
		{
			setInject(true);
			game->getGuiManager()->openGui();
		}
	}
}

void InputHandler::keyPressed(const OIS::KeyEvent& evt)
{
	switch(evt.key)
	{
	case OIS::KC_ESCAPE:
		exit(0);
		break;
	case OIS::KC_LCONTROL:
		toggleGui();
		break;
	}
	if(!getInject())
	{
		switch(evt.key)
		{
		case OIS::KC_SPACE: game->getPlayer()->getControl()->jump(); break;
		case OIS::KC_W: game->setForward(true); break;
		case OIS::KC_S: game->setBackward(true); break;
		case OIS::KC_A: game->setLeft(true); break;
		case OIS::KC_D: game->setRight(true); break;
		case OIS::KC_RETURN:
			if(game->getGuiManager()->getGui()->getName().compare("Hud") == 0)
			{
				Hud* hud = static_cast<Hud*>(game->getGuiManager()->getGui());
				hud->openChatBox();
				setInject(true);
			}
			break;
		}
	}
	else
	{
		switch(evt.key)
		{
		case OIS::KC_RETURN:
			Hud* hud = dynamic_cast<Hud*>(game->getGuiManager()->getGui());
			if(!game->getGuiManager()->isVisible() && hud->isChatBoxOpen())
			{
				hud->closeChatBox();
				setInject(false);

			}
			break;
		}
	}
}

void InputHandler::keyReleased(const OIS::KeyEvent& evt)
{
	if(!getInject())
	{
		switch(evt.key)
		{
		case OIS::KC_W: game->setForward(false); break;
		case OIS::KC_S: game->setBackward(false); break;
		case OIS::KC_A: game->setLeft(false); break;
		case OIS::KC_D: game->setRight(false); break;
		}
	}
}

void InputHandler::mouseMoved(const OIS::MouseEvent& evt)
{
	if(!getInject())
	{
		game->getCamEuler()->yaw(Ogre::Radian(-evt.state.X.rel * 0.0013)).pitch(Ogre::Radian(-evt.state.Y.rel * 0.0013)).setRoll(Ogre::Degree(0));
		if(game->getCamEuler()->getPitch() < Ogre::Degree(-90))
			game->getCamEuler()->setPitch(Ogre::Degree(-90));
		if(game->getCamEuler()->getPitch() > Ogre::Degree(90))
			game->getCamEuler()->setPitch(Ogre::Degree(90));
		game->getCamera()->setOrientation(*game->getCamEuler());
	}
}

void InputHandler::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	if(!getInject())
	{
		if(id == OIS::MB_Left)
		{	
			game->getAudioManager()->playGunshot();
			Ogre::Ray mouseRay(game->getCamera()->getDerivedPosition(), game->getCamera()->getDerivedDirection());
			Ogre::RaySceneQuery* mRaySceneQuery = game->getSceneManager()->createRayQuery(Ogre::Ray());
			mRaySceneQuery->setRay(mouseRay);
			mRaySceneQuery->setSortByDistance(true);
			Ogre::RaySceneQueryResult result = mRaySceneQuery->execute();
			Ogre::RaySceneQueryResult::iterator iter = result.begin();
			if(iter != result.end())
			{	
				try
				{
					if(iter->movable->getParentNode()->getName().substr(0,5).compare("enemy") == 0)
					{
						std::string name = iter->movable->getParentNode()->getName();
						game->getClient()->sendDamage(atoi(name.substr(name.find_first_of('_') + 1, name.size()).c_str()), 20);
					}
				}
				catch(int e){}
				Ogre::Vector3 camPos = game->getCamera()->getDerivedPosition();
				Ogre::Vector3 dir = game->getCamera()->getDerivedDirection();
				dir.normalise();
				Ogre::Vector3 right = game->getCamera()->getDerivedRight();
				right.normalise();
				Ogre::Vector3 up = game->getCamera()->getDerivedUp();
				up.normalise();
				Ogre::Vector3 arrowPos = camPos + 5 * dir + 2*right + -1*up;
				ProjectileManager::getSingleton().createLaser(game->getSceneManager(), arrowPos,mouseRay.getPoint(iter->distance));
			}
			delete mRaySceneQuery;
		}
	}
}

void InputHandler::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
}

void InputHandler::unbufferedInput(double tpf)
{
}