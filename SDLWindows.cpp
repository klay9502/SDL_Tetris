#include "SDLWindows.h"

#include <stdio.h>
#include <SDL_ttf.h>

SDLWindows::SDLWindows( void )
	: m_pWindow( nullptr )
	, m_pSocketServer( nullptr )
	, m_pGame( nullptr ) {}


bool SDLWindows::Init( unsigned int windowWidth, unsigned int windowHeight )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0)
	{
		fprintf( stderr, "SDL failed to initialize: %s\n",SDL_GetError() );
		return false;
	}

	fprintf( stdout, "SUCCESS::SDL Initialized\n" );

	m_pWindow = SDL_CreateWindow( "title",
								  SDL_WINDOWPOS_UNDEFINED,
								  SDL_WINDOWPOS_UNDEFINED,
								  windowWidth,
								  windowHeight,
								  SDL_WINDOW_SHOWN );

	if( !m_pWindow )
	{
		fprintf( stderr, "SDL failed to initialize: %s\n",SDL_GetError() );
		SDL_Quit();
		return false;
	}

	// SDL2_TTF

	if( TTF_Init() == -1 )
	{
		fprintf( stderr, "SDL2_TTL failed to initialize: %s\n",TTF_GetError() );
		return false;
	}

	fprintf( stdout, "SUCCESS::SDL2_TTF Initialized.\n" );

	// SocketServer

	m_pSocketServer = new SocketServer();

	if( !m_pSocketServer->Init() )
	{
		fprintf( stderr, "ERROR::SDLWindows - SocketServer class failed to initialize.\n" );
		return false;
	}

	if( !m_pGame->Init() )
	{
		fprintf( stderr, "Game class failed to initialize.\n" );
		return false;
	}

	return true;
}

void SDLWindows::Loop( void )
{
    int quit = 0;
	KeyEventValue keyEventBuf;

    while (!quit)
	{
		SDL_Event event;
        while( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			case SDL_QUIT:
				quit = 1;
				break;
				
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym )
				{
				case SDLK_ESCAPE:
					quit = 1;
					break;
				case SDLK_RIGHT:
				case SDLK_LEFT:
				case SDLK_UP:
				case SDLK_DOWN:
					keyEventBuf.SDLKValue = event.key.keysym.sym;
					if( send( m_pSocketServer->getSocket(), ( char* )&keyEventBuf, sizeof( keyEventBuf ), 0 ) == SOCKET_ERROR )
					{
						fprintf( stderr, "ERROR::SDLWindows - send() Error. Code: %d\n", WSAGetLastError() );
					}
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}
        }
    }
}

void SDLWindows::Release( void )
{
	m_pSocketServer->Release();
	delete m_pSocketServer;

	// SQL2_TTF
	TTF_Quit();

	SDL_DestroyWindow( m_pWindow );
	SDL_Quit();
}