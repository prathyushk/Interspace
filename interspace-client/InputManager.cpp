#include "InputManager.h"
#include <Ogre.h>
#include "Game.h"
#include <OgreRenderWindow.h>
#include "Euler.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "MainMenu.h"
#include "Gui.h"
#include "InputListener.h"

template<> InputManager* Ogre::Singleton<InputManager>::msSingleton = 0;

InputManager::InputManager(Ogre::RenderWindow* mWin, Game* inGame) 
	: mWindow(mWin), game(inGame)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	mInputManager = OIS::InputManager::createInputSystem( pl );
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, this ));
	mKeyboard->setTextTranslation(OIS::Keyboard::Unicode);
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, this ));
	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

InputManager::~InputManager()
{
	if(mWindow)
		windowClosed(mWindow);
}

OIS::Keyboard* InputManager::getKeyboard()
{
	return mKeyboard;
}

OIS::Mouse* InputManager::getMouse()
{
	return mMouse;
}

void InputManager::addListener(InputListener* listener)
{
	listeners.push_back(listener);
}

bool InputManager::mouseMoved(const OIS::MouseEvent& evt)
{
	for(int i = 0; i < listeners.size(); i++)
		listeners[i]->_mouseMoved(evt);
	return true;
}

bool InputManager::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	for(int i = 0; i < listeners.size(); i++)
		listeners[i]->_mousePressed(evt, id);
	return true;
}

bool InputManager::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	for(int i = 0; i < listeners.size(); i++)
		listeners[i]->_mouseReleased(evt, id);
	return true;
}

bool InputManager::keyPressed( const OIS::KeyEvent& evt )
{
	for(int i = 0; i < listeners.size(); i++)
		listeners[i]->_keyPressed(evt);
	return true;
}

bool InputManager::keyReleased( const OIS::KeyEvent& evt )
{
	for(int i = 0; i < listeners.size(); i++)
		listeners[i]->_keyReleased(evt);
	return true;
}



void InputManager::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
	CEGUI::System::getSingletonPtr()->notifyDisplaySizeChanged(CEGUI::Size(width,height));
}

bool InputManager::frameStarted(const Ogre::FrameEvent& evt)
{
	game->updatePhysics(evt.timeSinceLastFrame);
	return true;
}

bool InputManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;
	mKeyboard->capture();
	mMouse->capture();
	for(int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->_unbufferedInput(evt.timeSinceLastFrame);
		listeners[i]->update(evt.timeSinceLastFrame);
	}
	game->_update(evt.timeSinceLastFrame);
	return true;
}

bool InputManager::frameEnded(const Ogre::FrameEvent& evt)
{
	game->updatePhysics(evt.timeSinceLastFrame);
	return true;
}

void InputManager::windowClosed(Ogre::RenderWindow* rw)
{
	if( rw == mWindow )
	{
		if( mInputManager )
		{
			if(mMouse)
				mInputManager->destroyInputObject( mMouse );
			if(mKeyboard)
				mInputManager->destroyInputObject( mKeyboard );
			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}
