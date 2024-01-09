#ifndef __SDL_WINDOWS_H__
#define __SDL_WINDOWS_H__

#include <SDL.h>

#include "SocketServer.h"
#include "Game.h"

class SDLWindows
{
public:
	SDLWindows( void );

	bool Init( unsigned int windowWidth, unsigned int windowHeight );
	void Loop( void );
	void Release( void );

private:
	SDL_Window* m_pWindow;
	SocketServer* m_pSocketServer;
	Game* m_pGame;
};

#endif __SDL_WINDOWS_H__
