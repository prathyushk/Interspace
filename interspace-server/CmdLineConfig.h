#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX

#ifndef __CmdLineConfig_h__
#define __CmdLineConfig_h__

class CmdLineConfig {
 public:
  CmdLineConfig();
  void setScreenWidth(int);
  int getScreenWidth();
  void setScreenHeight(int);
  int getScreenHeight();
  void setFullscreen(bool);
  bool getFullscreen();
 private:
  int screenWidth;
  int screenHeight;
  bool fullscreen;
};

#endif /* __CmdLineConfig_h__ */

#endif
