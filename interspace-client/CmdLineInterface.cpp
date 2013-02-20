#include <Ogre.h>
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <getopt.h>

#include "CmdLineInterface.h"
#include "CmdLineConfig.h"


CmdLineInterface::CmdLineInterface(int argc, char *argv[]) {
  parseArgs(argc, argv);
}

CmdLineConfig CmdLineInterface::getConfig() {
  return config;
}

void CmdLineInterface::parseArgs(int argc, char *argv[]) {
  int screenWidth = 0;
  int screenHeight = 0;
  int resolutionChanged = 0;
  std::stringstream resolutionStream;

  for (;;) {
     static struct option long_options[] = {
       { "windowed",   no_argument,       0, 'w' },
       { "resolution", required_argument, 0, 'r' },
       { 0, 0, 0, 0 }
    };

    int option_index = 0;
    int option = getopt_long(argc, argv, "wr:", long_options, &option_index);

    if (option == -1) // End of Options
      break;

    switch (option) {
    case 0:
      break;
    case 'w':
      config.setFullscreen(false);
      break;
    case 'r':
      resolutionStream << optarg;
      resolutionChanged = 1;
      break;
    case '?':
      exit(127);
      break;
    default:
      abort();
    }
  }

  // Parse Resolution
  if (resolutionChanged) {
    std::vector<int> resolution = parseResolution(resolutionStream.str());
    if (config.getScreenWidth() != resolution.at(0) && config.getScreenHeight() != resolution.at(1))
      config.setFullscreen(false);
    config.setScreenWidth(resolution.at(0));
    config.setScreenHeight(resolution.at(1));
  }
}

std::vector<int> CmdLineInterface::parseResolution(std::string resolutionStr) {
  std::vector<int> resolution;
  for (unsigned i = 0; i < resolutionStr.length(); ++i) {
    if (resolutionStr.at(i) == 'x' || resolutionStr.at(i) == 'X') {
      // Get Width
      std::string widthStr = resolutionStr.substr(0, i);
      int width;
      std::stringstream(widthStr) >>width;
      resolution.push_back(width);
      
      // Get Height
      std::string heightStr = resolutionStr.substr(i + 1);
      int height;
      std::stringstream(heightStr) >>height;
      resolution.push_back(height);

      break;
    }
    if (i == resolutionStr.length() - 1) {
      std::cerr << "Invalid resolution argument" << std::endl;
      exit(127);
    }
  }

  if (resolution.at(0) > config.getScreenWidth() || resolution.at(1) > config.getScreenHeight()) {
    std::cout << "The specified resolution is larger than physical screen resolution" << std::endl;
    exit(127);
  }
  if (resolution.at(0) < 640 || resolution.at(1) < 480) {
    std::cout << "The specified resolution is smaller than the recommended resolution for playing Interspace (640x480). Continue (y/n)? ";
    char input;
    std::cin >>input;
    if (input != 'y' && input != 'Y')
      exit(127);
  }

  return resolution;
}

#endif

