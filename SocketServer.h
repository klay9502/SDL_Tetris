#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include <WinSock2.h>

typedef struct _KeyEventValue
{
	int SDLKValue;
} KeyEventValue;

class SocketServer
{
public:
	SocketServer(void);
	~SocketServer(void);

	bool Init( void );
	void Release( void );

	SOCKET getSocket( void );

private:
	WSADATA m_WSA;
	SOCKET m_Sock;
	SOCKADDR_IN m_ServerAddr;
	fd_set fd_Recv, fd_Send;
	fd_set cpyRecv, cpySend;
};

#endif