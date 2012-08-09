#ifndef __InputHandler_h_
#define __InputHandler_h_

class Game;
#include <OIS.h>
#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <Ogre.h>
#include "Euler.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

class InputHandler : public Ogre::WindowEventListener, public Ogre::FrameListener, public OIS::MouseListener, public OIS::KeyListener
{
public:
	InputHandler(Ogre::RenderWindow*, Game*);
	~InputHandler(void);
protected:
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);
	virtual bool mouseMoved( const OIS::MouseEvent& evt);
	virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
	virtual bool keyPressed( const OIS::KeyEvent& evt );
    virtual bool keyReleased( const OIS::KeyEvent& evt );
	
private:
	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	Ogre::RenderWindow* mWindow;
	Game* game;
};

#endif