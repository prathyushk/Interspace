#include "InputListener.h"
#include <OIS.h>
#include <CEGUI.h>

InputListener::InputListener()
	: ceguiInject(false)
{
}

InputListener::~InputListener()
{
}

void InputListener::_keyPressed(const OIS::KeyEvent& evt)
{
	if(ceguiInject)
	{
		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectKeyDown(evt.key);
		sys.injectChar(evt.text);
		begin(evt);
	}
	keyPressed(evt);
}

void InputListener::_keyReleased(const OIS::KeyEvent& evt)
{
	if(ceguiInject)
	{
		CEGUI::System::getSingleton().injectKeyUp(evt.key);
		end(evt);
	}
	keyReleased(evt);
}

void InputListener::_mouseMoved(const OIS::MouseEvent& evt)
{
	if(ceguiInject)
	{
		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
		if (evt.state.Z.rel)
			sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
	}
	mouseMoved(evt);
}

void InputListener::_mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	if(ceguiInject)
		CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
	mousePressed(evt,id);
}

void InputListener::_mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	if(ceguiInject)
		CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
	mouseReleased(evt,id);
}

void InputListener::_unbufferedInput(double tpf)
{
	if(ceguiInject)
		CEGUI::System::getSingleton().injectTimePulse(tpf);
	unbufferedInput(tpf);
}

void InputListener::setInject(bool inject)
{
	ceguiInject = inject;
}

bool InputListener::getInject()
{
	return ceguiInject;
}

void InputListener::repeatKey(OIS::KeyCode a_nKey, unsigned int a_nChar)
{
	CEGUI::System::getSingleton().injectKeyUp(a_nKey);
	CEGUI::System::getSingleton().injectKeyDown(a_nKey);
	CEGUI::System::getSingleton().injectChar(a_nChar);
};

CEGUI::MouseButton InputListener::convertButton(OIS::MouseButtonID buttonID)
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