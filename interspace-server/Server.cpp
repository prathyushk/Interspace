
#include "Server.h"
#include "Client.h"
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <vector>
#include <iostream>
#include "PhysicsManager.h"
#include <ctime>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CLIENTS 10
#define SERVER_PORT 6262

Server::Server(void)
  : enemies(new std::vector<Enemy*>()),
    clients(new std::vector<Client*>())
{
	srand(time(NULL));
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(SERVER_PORT,0);
	peer->Startup(MAX_CLIENTS, &sd, 1);
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	phys = new PhysicsManager();
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(btVector3(0,0,0));
	btRigidBody *RigidBody = phys->addRigidBody(Transform,new btStaticPlaneShape(btVector3(0,1,0),0),0);
	addEnemies(10);
}

Server::~Server(void)
{
	delete phys;
	for(int i = 0; i < clients->size(); i++)
	  delete clients->at(i);
	delete packet;
	delete clients;
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

int Server::enemiesCalculate()
{
	while(true)
	{
		for(int i = 0; i < enemies->size(); i++)
		{
			int rand = 0 + (std::rand() % (int)(7 - 0 + 1));
			switch(rand)
			{
			case 0:
				enemies->at(i)->setWalkDirection(btVector3(0.25f,0,0));
				break;
			case 1:
				enemies->at(i)->setWalkDirection(btVector3(-0.25f,0,0));
				break;
			case 2:
				enemies->at(i)->setWalkDirection(btVector3(0,0,0.25f));
				break;
			case 3:
				enemies->at(i)->setWalkDirection(btVector3(0,0,-0.25f));
				break;
			case 4:
				enemies->at(i)->setWalkDirection(btVector3(0.25f,0,0.25f));
				break;
			case 5:
				enemies->at(i)->setWalkDirection(btVector3(-0.25f,0,0.25f));
				break;
			case 6:
				enemies->at(i)->setWalkDirection(btVector3(-0.25f,0,-0.25f));
				break;
			case 7:
				enemies->at(i)->setWalkDirection(btVector3(0.25f,0,-0.25f));
				break;
			}
			
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(5000));
	}
}

int Server::enemiesTarget()
{
	while(true)
	{
		for(int i = 0; i < enemies->size(); i++)
		{
		  if(enemies->at(i)->getTarget() == NULL && clients->size() > 0)
			{
			  for(int j = 0; j < clients->size(); j++)
				{
				  Client* target = getClientAt(j);
				  if (target != NULL) {
				    if(target->getPos().distance(enemies->at(i)->getPosition()) <= enemies->at(i)->getFov())
				      enemies->at(i)->setTarget(target);
				  }
				}
			}
			else if(enemies->at(i)->getTarget() != NULL)
			{
				if(enemies->at(i)->getTarget()->getPos().distance(enemies->at(i)->getPosition()) <= enemies->at(i)->getFov())
				{
				  if((rand() % 10) == 0)
				    sendPlayerDamage(std::distance(clients->begin(), std::find(clients->begin(),clients->end(),enemies->at(i)->getTarget())), enemies->at(i)->getDamage());
				}
				else
					enemies->at(i)->setTarget(NULL);
			}
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}

int Server::listenForMessages()
{
	while(true)
	{
		
		for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			switch(packet->data[0])
			{
			case ID_NEW_INCOMING_CONNECTION:
				std::cout << packet->systemAddress.ToString() << " has connected" << std::endl;
				newConnection(packet);
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				std::cout << packet->systemAddress.ToString() << " has disconnected" << std::endl;
				clientDisconnected(packet);
				break;
			case ID_CONNECTION_LOST:
				std::cout << packet->systemAddress.ToString() << " has lost connection" << std::endl;
				clientDisconnected(packet);
				break;
			case PLAYER_MOVE_MESSAGE:
				playerMoveMessageReceived(packet);
				break;
			case ENEMY_DAMAGE_MESSAGE:
				enemyDamageReceived(packet);
				break;
			case CHAT_MESSAGE:
			        chatMessageRecieved(packet);
				break;
			}
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

void Server::chatMessageRecieved(RakNet::Packet* packet)
{
        RakNet::RakString rs;
        RakNet::BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(rs);
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)CHAT_MESSAGE);
	bsOut.Write(rs);
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_RAKNET_GUID,true);
}

void Server::enemyDamageReceived(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int index, damage;
	bsIn.Read(index);
	bsIn.Read(damage);
	enemies->at(index)->takeDamage(damage);
}

void Server::addEnemies(int num)
{
	for(int i = 0; i < num; i++)
	{
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(0, 100, 10));
		enemies->push_back(new Enemy(3,300,100,i,new btCapsuleShape(5,15),transform,phys));
	}
}

void Server::start()
{
	time_t ti = time(NULL);
	std::cout << "The server has been started" << std::endl;
	boost::thread thr1(boost::bind(&Server::enemiesCalculate, this));
	boost::thread thr2(boost::bind(&Server::listenForMessages, this));
	boost::thread thr3(boost::bind(&Server::enemiesTarget, this));
	while (1)
	{
		boost::mutex::scoped_lock lock(enemiesMutex);
		phys->update(1/1000.f * 3);
		for(int i = 0; i < enemies->size(); i++)
			enemies->at(i)->update();
		sendEnemyPositions();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

void Server::sendEnemyPositions()
{
	for(int i = 0; i < enemies->size(); i++)
	{
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID) ENEMY_MOVE_MESSAGE);
		bsOut.Write(i);
		btVector3 pos = enemies->at(i)->getPosition();
		btVector3 dir = enemies->at(i)->getDirection();
		bsOut.Write((float)pos.x());
		bsOut.Write((float)pos.y());
		bsOut.Write((float)pos.z());
		bsOut.Write((float)dir.x());
		bsOut.Write((float)dir.y());
		bsOut.Write((float)dir.z());
		peer->Send(&bsOut,IMMEDIATE_PRIORITY,UNRELIABLE,0,RakNet::UNASSIGNED_RAKNET_GUID,true);
		bsOut.Reset();
	}
}

void Server::sendPlayerDamage(int playerIndex, int damage)
{
  RakNet::BitStream bsOut;
  bsOut.Write((RakNet::MessageID) PLAYER_DAMAGE_MESSAGE);
  bsOut.Write((int)playerIndex);
  bsOut.Write((int)damage);
  peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,getClientAt(playerIndex)->getGuid(),false);
  bsOut.Reset();
}

void Server::playerMoveMessageReceived(RakNet::Packet* pack)
{
	RakNet::BitStream bsIn(pack->data,pack->length,false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int index;
	int posx, posy, posz, dirx, diry, dirz;
	RakNet::RakString str;
	bsIn.Read(index);
	bsIn.Read(str);
	bsIn.Read(posx);
	bsIn.Read(posy);
	bsIn.Read(posz);
	bsIn.Read(dirx);
	bsIn.Read(diry);
	bsIn.Read(dirz);
	Client* movedPlayer = getClientAt(index);
	if (movedPlayer != NULL) {
	  movedPlayer->setPos(btVector3(static_cast<btScalar>(posx), static_cast<btScalar>(posy), static_cast<btScalar>(posz)));
	  RakNet::BitStream bsOut;
	  bsOut.Write((RakNet::MessageID) PLAYER_MOVE_MESSAGE);
	  bsOut.Write(index);
	  bsOut.Write(str);
	  bsOut.Write(posx);
	  bsOut.Write(posy);
	  bsOut.Write(posz);
	  bsOut.Write(dirx);
	  bsOut.Write(diry);
	  bsOut.Write(dirz);
	  peer->Send(&bsOut,IMMEDIATE_PRIORITY,UNRELIABLE,0, RakNet::UNASSIGNED_RAKNET_GUID,true);
	  bsOut.Reset();
	}
}

void Server::newConnection(RakNet::Packet* pack)
{
  clients->push_back(new Client(pack->guid, clients->size()));
  RakNet::BitStream bsOut;
  bsOut.Write((RakNet::MessageID)PLAYER_JOINED_MESSAGE);
  bsOut.Write((int)(clients->size() - 1));
  peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0, RakNet::UNASSIGNED_RAKNET_GUID,true);
   bsOut.Reset();
}

void Server::clientDisconnected(RakNet::Packet* pack)
{
	int discIndex = -1;
	for(int i = 0; i < clients->size() ; i++)
	{
	  if(clients->at(i)->getGuid() == pack->guid)
	        {
			discIndex = i;
			break;
		}
	}
	if(discIndex != -1)
	{
	  for(int i = 0; i < enemies->size(); i++)
	    {
	      if(enemies->at(i)->getTarget() == clients->at(discIndex))
		 enemies->at(i)->setTarget(NULL);
	    }
	  delete clients->at(discIndex);
	  clients->erase(clients->begin() + discIndex);
	  for(int i = 0; i < clients->size(); i++)
		{
		  clients->at(i)->setIndex(i);
		}
	  if(clients->size() > 0){
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID) PLAYER_LEFT_MESSAGE);
			bsOut.Write(discIndex);
			peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0, RakNet::UNASSIGNED_RAKNET_GUID,true);
			bsOut.Reset();
		}
	}
 }

Client* Server::getClientAt(int index) 
{
  if (index < clients->size())
    return clients->at(index);
  else
    return NULL;
}
