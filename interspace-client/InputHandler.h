#ifndef __InputHandler_h__
#define __InputHandler_h__

class Interspace;
#include "InputListener.h"

class InputHandler : public InputListener
{
public:
	InputHandler();
	~InputHandler();
	void keyPressed(const OIS::KeyEvent& evt);
	void keyReleased(const OIS::KeyEvent& evt);
	void mouseMoved(const OIS::MouseEvent& evt);
	void mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	void mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	void unbufferedInput(double tpf);
private:
	void toggleGui();
	Interspace* game;
};

#endif