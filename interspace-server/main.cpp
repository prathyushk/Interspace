#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Game.h"
#include <iostream>
#include <OgreException.h>
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include "CmdLineConfig.h"
#include "CmdLineInterface.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
      CmdLineInterface *cmdLine = new CmdLineInterface(argc, argv);
      CmdLineConfig config = cmdLine->getConfig();
      delete cmdLine;
      Game app(config);
#else
      Game app;
#endif
 
        try {
            app.start();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif
