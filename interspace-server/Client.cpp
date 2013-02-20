#include "Client.h"
#include <boost/thread.hpp>
#include <RakPeerInterface.h>
#include <btBulletDynamicsCommon.h>

Client::Client(RakNet::RakNetGUID& setGuid, int inputIndex)
{
	index = inputIndex;
	guid = setGuid;
}

Client::~Client(void)
{
}

int Client::getIndex()
{
	return index;
}

void Client::setIndex(int inputIndex)
{
	index = inputIndex;
}

void Client::setPos(const btVector3& vec)
{
	pos = vec;
}

btVector3& Client::getPos()
{
	return pos;
}

RakNet::RakNetGUID& Client::getGuid()
{
	return guid;
}
