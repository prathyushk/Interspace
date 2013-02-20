#ifndef __Client_h_
#define __Client_h_

#include <boost/thread.hpp>
#include <RakPeerInterface.h>
#include <btBulletDynamicsCommon.h>

class Client
{
public:
	Client(RakNet::RakNetGUID&, int index);
	~Client(void);
	void setPos(const btVector3&);
	btVector3& getPos(void);
	RakNet::RakNetGUID& getGuid(void);
	int getIndex(void);
	void setIndex(int set);
private:
	RakNet::RakNetGUID guid;
	btVector3 pos;
	int index;
};

#endif

