#ifndef __Client_h_
#define __Client_h_

class Interspace;
class Hud;
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include "Ogre.h"
#include <string>

class Client : public Ogre::Singleton<Client>
{
public:
	Client();
	~Client(void);
	void update(void);
	void sendMessage(std::string str);
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
		ENEMY_DAMAGE_MESSAGE=ID_USER_PACKET_ENUM+5,
		CHAT_MESSAGE=ID_USER_PACKET_ENUM+6,
		PLAYER_DAMAGE_MESSAGE=ID_USER_PACKET_ENUM+7
	};
	void enemyMoveMessageReceived(RakNet::Packet* packet);
	void playerMoveMessageReceived(RakNet::Packet* packet);
	void playerJoined(RakNet::Packet* packet);
	void playerLeft(RakNet::Packet* packet);
	void chatMessageRecieved(RakNet::Packet* packet);
	void playerDamageRecieved(RakNet::Packet* packet);
	Interspace* game;
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	RakNet::SystemAddress serverAddress;
	bool connected;
};

#endif