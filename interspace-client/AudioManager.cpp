#include "AudioManager.h"
#include <OgreOggSound.h>

AudioManager::AudioManager()
	: gunShots(0)
{
	mSoundMgr = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
	mSoundMgr->init();
	
}

void AudioManager::playMain()
{
	OgreOggSound::OgreOggISound* mainSong = mSoundMgr->createSound("background", "DST-TacticalSpace.ogg", true, true, false);
	mainSong->disable3D(true);
	mainSong->play();
}

void AudioManager::playGunshot()
{
	OgreOggSound::OgreOggISound* gunShot = mSoundMgr->createSound("gunShot" + std::to_string(static_cast<long long>(gunShots)), "laser.ogg", false, false, false, NULL, true);
	gunShot->markTemporary();
	gunShot->disable3D(true);
	gunShot->setVolume(0.3);
	gunShots++;
	gunShot->play(true);
}

void AudioManager::update(double dt)
{
	mSoundMgr->update(dt);
}
