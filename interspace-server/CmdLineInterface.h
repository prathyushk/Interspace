#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX

#ifndef __CmdLineInterface_h__
#define __CmdLineInterface_h__

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
