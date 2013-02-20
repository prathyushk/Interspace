#ifndef __Server_h_
#define __Server_h_

#include "Client.h"
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <vector>
#include <string>
#include <iostream>
#include "PhysicsManager.h"
#include "Enemy.h"
#include <boost/thread.hpp>

class Server
{
public:
	Server(void);
	~Server(void);
	void start(void);
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
	boost::mutex enemiesMutex;
	void sendEnemyPositions(void);
	void sendPlayerDamage(int playerIndex, int damage);
	int enemiesTarget(void);
	int enemiesCalculate(void);
	int listenForMessages(void);
	void addEnemies(int num);
	std::vector<Enemy*>* enemies;
	PhysicsManager* phys;
	std::vector<Client*>* clients;
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	void enemyDamageReceived(RakNet::Packet*);
	void newConnection(RakNet::Packet*);
	void clientDisconnected(RakNet::Packet*);
	void playerMoveMessageReceived(RakNet::Packet*);
	void chatMessageRecieved(RakNet::Packet*);
	Client* getClientAt(int);
};

#endif
