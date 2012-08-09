#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX

#include <cstdlib>
#include <iostream>
#include <X11/Xlib.h>

#include "CmdLineConfig.h"
#include "CmdLineInterface.h"

CmdLineConfig::CmdLineConfig() {
  // Set Defaults
  fullscreen = true;
  Display *dsp = NULL;
  Screen *scr = NULL;
  dsp = XOpenDisplay(NULL);
  if (! dsp) {
    std::cerr << "Unable to open display" << std::endl;
    exit(-1);
  }
  scr = DefaultScreenOfDisplay(dsp);
  if (! scr) {
    std::cerr << "Unable to open default screen of display" << std::endl;
    exit(-1);
  }
  screenWidth = scr->width;
  screenHeight = scr->height;
  XCloseDisplay(dsp);
}

void CmdLineConfig::setScreenWidth(int inputScreenWidth) {
  screenWidth = inputScreenWidth;
}

int CmdLineConfig::getScreenWidth() {
  return screenWidth;
}

void CmdLineConfig::setScreenHeight(int inputScreenHeight) {
  screenHeight = inputScreenHeight;
}

int CmdLineConfig::getScreenHeight() {
  return screenHeight;
}

void CmdLineConfig::setFullscreen(bool inputFullscreen) {
  fullscreen = inputFullscreen;
}

bool CmdLineConfig::getFullscreen() {
  return fullscreen;
}

#endif
