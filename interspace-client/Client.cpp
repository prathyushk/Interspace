#include "Client.h"
#include <MessageIdentifiers.h>
#include <Ogre.h>
#include <BitStream.h>
#include "Person.h"
#include "Interspace.h"
#include <btBulletDynamicsCommon.h>
#include "PhysicsManager.h"
#include "Euler.h"
#include "GuiManager.h"
#include "Hud.h"

#define SERVER_PORT 6262

template<> Client* Ogre::Singleton<Client>::msSingleton = 0;

Client::Client() : game(Interspace::getSingletonPtr()), connected(false)
{
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd;
	peer->Startup(1,&sd, 1);
	peer->SetMaximumIncomingConnections(100);
	peer->Connect("198.23.226.17",SERVER_PORT,0,0); 
}

Client::~Client()
{
	if(packet)
		delete packet;
	peer->Shutdown(3,0,IMMEDIATE_PRIORITY);
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

void Client::update()
{
	for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
	{
		switch(packet->data[0])
		{
		case ENTITY_POSITION_MESSAGE:
			entityPositionReceived(packet);
			break;
		case ENEMY_DAMAGE_MESSAGE:
			enemyDamageRecieved(packet);
			break;
		case PLAYER_DAMAGE_MESSAGE:
			playerDamageRecieved(packet);
			break;
		case CHAT_MESSAGE:
			chatMessageRecieved(packet);
			break;
		case ENEMY_MOVE_MESSAGE:
			enemyMoveMessageReceived(packet);
			break;
		case PLAYER_MOVE_MESSAGE:
			playerMoveMessageReceived(packet);
			break;
		case PLAYER_JOINED_MESSAGE:
			playerJoined(packet);
			break;
		case PLAYER_LEFT_MESSAGE:
			playerLeft(packet);
			break;
		case ID_CONNECTION_ATTEMPT_FAILED:
			exit(0);
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			exit(0);
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			break;
		}
	}
}

bool Client::isConnected()
{
	return connected;
}

void Client::entityPositionReceived(RakNet::Packet* packet)
{
	if(connected)
	{
		RakNet::BitStream bsIn(packet->data,packet->length,false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
		int type, index, posx,posy,posz, dirx,diry,dirz;
		bsIn.Read(type); bsIn.Read(index); bsIn.Read(posx); bsIn.Read(posy); bsIn.Read(posz);
		if(type == 0);

	}
}

void Client::chatMessageRecieved(RakNet::Packet* packet)
{
	if(connected)
	{
		RakNet::RakString rs;
		RakNet::BitStream bsIn(packet->data,packet->length,false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
		bsIn.Read(rs);
		if(game->getGuiManager()->getGui()->getName().compare("Hud") == 0)
		{
			Hud* hud = static_cast<Hud*>(game->getGuiManager()->getGui());
			hud->addToChat(rs.C_String());
		}
	}
}

void Client::playerDamageRecieved(RakNet::Packet* packet)
{
	if(connected)
	{
		RakNet::BitStream bsIn(packet->data,packet->length,false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
		unsigned short i;
		unsigned short d;
		bsIn.Read(i);
		bsIn.Read(d);
		int index = (int) i;
		int damage = (int) d;
		if(index == game->getIndex())
		{
			game->getPlayer()->takeDamage(damage);
			game->getAudioManager()->playGunshot();
		}
	}
}

void Client::enemyDamageRecieved(RakNet::Packet* packet)
{
	if(connected)
	{
		RakNet::BitStream bsIn(packet->data,packet->length,false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
		unsigned short i, pI, h;
		bsIn.Read(i);
		bsIn.Read(pI);
		bsIn.Read(h);
		int index = (int)i;
		int playerIndex = (int)pI;
		int health = (int)h;
		game->getEnemies()->at(index)->setHealth(health);
		if(playerIndex == game->getIndex())
			game->getEnemies()->at(index)->checkDeath(game->getPlayer());
	}
}

void Client::sendMessage(std::string str)
{
	if(connected)
	{
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)CHAT_MESSAGE);
		bsOut.Write(str.c_str());
		peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,serverAddress,false);
	}
}


void Client::sendDamage(int index, int damage)
{
	if(connected)
	{
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ENEMY_DAMAGE_MESSAGE);
		bsOut.Write((unsigned short)index);
		bsOut.Write((unsigned short)game->getIndex());
		bsOut.Write((unsigned short)damage);
		peer->Send(&bsOut, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, false);
	}
}

void Client::enemyMoveMessageReceived(RakNet::Packet* packet)
{
	if(connected)
	{
		RakNet::BitStream bsIn(packet->data,packet->length,false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
		unsigned short i;
		float posx, posy, posz, dirx, diry, dirz;
		bsIn.Read(i);
		bsIn.ReadVector(posx, posy, posz);
		bsIn.ReadVector(dirx,diry,dirz);
		int index = (int)i;
		game->getEnemies()->at(index)->setPosition(Ogre::Vector3(posx,posy,posz));
		Ogre::Vector3 vec(dirx,diry,dirz);
		Ogre::Euler euler;
		euler.setDirection(vec * -1);
		game->getEnemies()->at(index)->setOrientation(euler.toQuaternion());
	}
}

void Client::playerMoveMessageReceived(RakNet::Packet* packet)
{
	if(connected)
	{
		RakNet::BitStream bsIn(packet->data,packet->length,false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
		unsigned short i;
		float posx, posy, posz, dirx, diry, dirz;
		RakNet::RakString rs;
		bsIn.Read(i);
		bsIn.Read(rs);
		bsIn.ReadVector(posx,posy,posz);
		bsIn.ReadVector(dirx,diry,dirz);
		int index = (int)i;
		game->getPlayers()->at(index)->setPosition(Ogre::Vector3(posx,posy,posz));
		if(index != game->getIndex())
			game->getPlayers()->at(index)->changeName(rs.C_String());
		Ogre::Euler euler;
		euler.setYaw(Ogre::Degree(dirx)).setPitch(Ogre::Degree(diry)).setRoll(Ogre::Degree(dirz));
		game->getPlayers()->at(index)->getNode()->setOrientation(euler);
	}
}

void Client::playerJoined(RakNet::Packet* packet)
{
	serverAddress = packet->systemAddress;
	RakNet::BitStream bsIn(packet->data, packet->length,false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	unsigned short i;
	bsIn.Read(i);
	int index = (int)i;
	if(game->getIndex() == -1){
		game->setIndex(index);
		for(int i = 0; i < game->getIndex() + 1; i++){
			Player* person = new Player(game->getSceneManager()->createEntity("Oto.mesh"), game->getSceneManager()->getRootSceneNode()->createChildSceneNode(), "Player", Ogre::Vector3(0,10,80), new btCapsuleShape(5,25), 4);
			game->getPlayers()->push_back(person);
			if(i == game->getIndex()){
				int h = game->getPlayers()->size();
				game->getPlayers()->at(game->getIndex())->getNode()->setVisible(false);
				game->getPlayers()->at(game->getIndex())->getNode()->detachAllObjects();
			}
		}
		connected = true;
	}
	else
		game->getPlayers()->push_back(new Player(game->getSceneManager()->createEntity("Oto.mesh"),
		game->getSceneManager()->getRootSceneNode()->createChildSceneNode(), "Player", Ogre::Vector3(0,10,80), new btCapsuleShape(5,25),4));
}

void Client::playerLeft(RakNet::Packet* packet)
{
	if(connected)
	{
		RakNet::BitStream bsIn(packet->data,packet->length,false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
		unsigned short vx;
		bsIn.Read(vx);
		int vecx = (int)vx;
		delete game->getPlayers()->at(vecx);
		game->getPlayers()->erase(game->getPlayers()->begin() + vecx);
		if(vecx < game->getIndex())
			game->setIndex(game->getIndex() - 1);
	}
}

void Client::sendPosition(const Ogre::Vector3 vec, const Ogre::Vector3 dir)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)PLAYER_MOVE_MESSAGE);
	bsOut.Write((unsigned short)game->getIndex());
	bsOut.Write(game->getPlayer()->getName().c_str());
	bsOut.WriteVector((float)vec.x,(float)vec.y,(float)vec.z);
	bsOut.WriteVector((float)dir.x,(float)dir.y,(float)dir.z);
	peer->Send(&bsOut,IMMEDIATE_PRIORITY,UNRELIABLE,0,serverAddress,false);
}
