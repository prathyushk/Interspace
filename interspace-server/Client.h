#ifndef __Client_h__
#define __Client_h__

class Game;
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include "Ogre.h"

class Client
{
public:
	Client(Game*);
	~Client(void);
	void update(void);
	void sendDamage(int index, int damage);
	void sendPosition(const Ogre::Vector3 position, const Ogre::Vector3 direction);
	bool isConnected(void);
private:
	enum GameMessages
	{
		PLAYER_JOINED_MESSAGE=ID_USER_PACKET_ENUM+1,
		PLAYER_LEFT_MESSAGE=ID_USER_PACKET_ENUM+2,
		PLAYER_MOVE_MESSAGE=ID_USER_PACKET_ENUM+3,
		ENEMY_MOVE_MESSAGE=ID_USER_PACKET_ENUM+4,
		ENEMY_DAMAGE_MESSAGE=ID_USER_PACKET_ENUM+5
	};
	void enemyMoveMessageReceived(RakNet::Packet* packet);
	void playerMoveMessageReceived(RakNet::Packet* packet);
	void playerJoined(RakNet::Packet* packet);
	void playerLeft(RakNet::Packet* packet);
	Game* game;
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	RakNet::SystemAddress serverAddress;
	bool connected;
};

#endif