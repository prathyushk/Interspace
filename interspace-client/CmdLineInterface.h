#include <Ogre.h>
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX

#ifndef __CmdLineInterface_h_
#define __CmdLineInterface_h_

#include <vector>
#include <sstream>

#include "CmdLineConfig.h"

class CmdLineInterface {
 public:
  CmdLineInterface(int, char**);
  CmdLineConfig getConfig();
 private:
  void parseArgs(int, char**);
  std::vector<int> parseResolution(std::string);
  CmdLineConfig config;
};

#endif /* __CmdLineInterface_h__ */

#endif
