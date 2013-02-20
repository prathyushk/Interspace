#include "Server.h"

int main()
{
	Server* server = new Server();
	server->start();
	delete server;
	return 0;
}