#ifndef __InputListener_h__
#define __InputListener_h__

#include <OIS.h>
#include <CEGUI.h>
#include "AutoRepeatKey.h"

class InputListener : public AutoRepeatKey
{
public:
	InputListener();
	virtual ~InputListener();
	void _keyPressed(const OIS::KeyEvent& evt);
	void _keyReleased(const OIS::KeyEvent& evt);
	void _mouseMoved(const OIS::MouseEvent& evt);
	void _mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	void _mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	void _unbufferedInput(double tpf);
	void setInject(bool inject);
	bool getInject();
protected:
	void repeatKey(OIS::KeyCode a_nKey, unsigned int a_nChar);
	virtual void keyPressed(const OIS::KeyEvent& evt)=0;
	virtual void keyReleased(const OIS::KeyEvent& evt)=0;
	virtual void mouseMoved(const OIS::MouseEvent& evt)=0;
	virtual void mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)=0;
	virtual void mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)=0;
	virtual void unbufferedInput(double tpf)=0;
private:
	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
	bool ceguiInject;
};

#endif