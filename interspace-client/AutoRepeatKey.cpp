#include "AutoRepeatKey.h"
 
AutoRepeatKey::AutoRepeatKey(float a_fRepeatDelay, float a_fInitialDelay):
    m_nKey(OIS::KC_UNASSIGNED),
    m_fRepeatDelay(a_fRepeatDelay),
    m_fInitialDelay(a_fInitialDelay)
{}
 
void AutoRepeatKey::begin(const OIS::KeyEvent &evt) {
    m_nKey = evt.key;
    m_nChar = evt.text;
 
    m_fElapsed = 0;
    m_fDelay = m_fInitialDelay;
}
 
void AutoRepeatKey::end(const OIS::KeyEvent &evt) {
    if (m_nKey != evt.key) return;
 
    m_nKey = OIS::KC_UNASSIGNED;
}
 
void AutoRepeatKey::update(float a_fElapsed) {
    if (m_nKey == OIS::KC_UNASSIGNED) return;
 
    m_fElapsed += a_fElapsed;
    if (m_fElapsed < m_fDelay) return;
 
    m_fElapsed -= m_fDelay;
    m_fDelay = m_fRepeatDelay;
 
    do {
        repeatKey(m_nKey, m_nChar);
 
        m_fElapsed -= m_fRepeatDelay;
    } while (m_fElapsed >= m_fRepeatDelay);
 
    m_fElapsed = 0;
}