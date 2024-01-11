#include "SocketServer.h"

#include <stdio.h>

SocketServer::SocketServer(void)
{
}


SocketServer::~SocketServer(void)
{
}

bool SocketServer::Init( void )
{
	if( WSAStartup( MAKEWORD( 2, 2 ), &m_WSA ) != 0 )
	{
		fprintf( stderr, "ERROR::SocketServer - Failed WSAStartup.\n");
		return false;
	}
	
	m_Sock = socket( AF_INET, SOCK_STREAM, 0 );

	if( m_Sock == INVALID_SOCKET )
	{
		fprintf( stderr, "ERROR::SocketServer - Invalid Socket.\n");
		return false;
	}

	ZeroMemory( &m_ServerAddr, sizeof( m_ServerAddr ) );
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	m_ServerAddr.sin_port = htons( 9000 );
	
	// 연결 시도
	if( connect( m_Sock, ( SOCKADDR* )&m_ServerAddr, sizeof( m_ServerAddr ) ) == SOCKET_ERROR )
	{
		fprintf( stderr, "ERROR::SocketServer - SOCKET_ERROR in connect func.\n");
		// system("pause");
		return false;
	}

	FD_ZERO( &fd_Recv );
	FD_ZERO( &cpyRecv );
	FD_ZERO( &fd_Send );
	FD_ZERO( &cpySend );

	FD_SET( m_Sock, &fd_Recv );
	FD_SET( m_Sock, &fd_Send );

	return true;
}

void SocketServer::Release( void )
{
	
}

SOCKET SocketServer::getSocket( void )
{
	return m_Sock;
}