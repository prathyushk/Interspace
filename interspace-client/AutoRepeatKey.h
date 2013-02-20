#ifndef __AutoRepeatKey_h_
#define __AutoRepeatKey_h_

#include <OIS.h>
 
class AutoRepeatKey {
private:
    OIS::KeyCode m_nKey;
    unsigned int m_nChar;
 
    float m_fElapsed;
    float m_fDelay;
 
    float m_fRepeatDelay;
    float m_fInitialDelay;
 
protected:
 
    virtual void repeatKey(OIS::KeyCode a_nKey, unsigned int a_nChar) = 0;
 
public:
 
    AutoRepeatKey(float a_fRepeatDelay = 0.035f, float a_fInitialDelay = 0.300f);
 
    void begin(const OIS::KeyEvent &evt);
 
    void end(const OIS::KeyEvent &evt);
 
    void update(float a_fElapsed); // Elapsed time in seconds
};

#endif /* __AutoRepeatKey_h_ */