#ifndef __AudioManager_h_
#define __AudioManager_h_

#include <OgreOggSoundManager.h>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void playMain(void);
	void playGunshot(void);
private:
	int gunShots;
	OgreOggSound::OgreOggSoundManager* mSoundMgr;
};

#endif