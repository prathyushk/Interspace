#include "InputHandler.h"
#include <Ogre.h>
#include "Game.h"
#include <OgreRenderWindow.h>
#include "Euler.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "MainMenu.h"
#include "Gui.h"


InputHandler::InputHandler(Ogre::RenderWindow* mWin, Game* main) : game(main), mWindow(mWin)
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
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, this ));
	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

InputHandler::~InputHandler(void)
{
	if(mWindow)
		windowClosed(mWindow);
}

bool InputHandler::mouseMoved(const OIS::MouseEvent& evt)
{
	if(game->getGui()->isVisible())
	{
		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
		if (evt.state.Z.rel)
			sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
	}
	else
		game->injectMouseMoved(evt.state.X.rel, evt.state.Y.rel);
	return true;
}

bool InputHandler::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	if(game->getGui()->isVisible())
		CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
	else
		game->injectMousePressed(id);
	return true;
}
bool InputHandler::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	if(game->getGui()->isVisible())
		CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
	else
		game->injectMouseReleased(id);
	return true;
}

bool InputHandler::keyPressed( const OIS::KeyEvent& evt )
{
	if(game->getGui()->isVisible())
	{
		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectKeyDown(evt.key);
		sys.injectChar(evt.text);
	}
	else
		game->injectKeyPressed(evt.key);
	game->injectGuiKeyPressed(evt.key);
	return true;
}

CEGUI::MouseButton InputHandler::convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

bool InputHandler::keyReleased( const OIS::KeyEvent& evt )
{
	if(game->getGui()->isVisible())
		CEGUI::System::getSingleton().injectKeyUp(evt.key);
	else
		game->injectKeyReleased(evt.key);
	return true;
}


void InputHandler::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
	CEGUI::System::getSingletonPtr()->notifyDisplaySizeChanged(CEGUI::Size(width,height));
}

bool InputHandler::frameStarted(const Ogre::FrameEvent& evt)
{
	game->updatePhysics(evt.timeSinceLastFrame);
	return true;
}

bool InputHandler::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;
	mKeyboard->capture();
	mMouse->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;
	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
	game->update(evt.timeSinceLastFrame);
	return true;
}

bool InputHandler::frameEnded(const Ogre::FrameEvent& evt)
{
	game->updatePhysics(evt.timeSinceLastFrame);
	return true;
}

void InputHandler::windowClosed(Ogre::RenderWindow* rw)
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
