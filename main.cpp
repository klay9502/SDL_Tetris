#include "SDLWindows.h"

#include <stdio.h>

#define DISPLAY_WIDTH	1280
#define DISPLAY_HEIGHT	720

int main( int argc, char* argv[] )
{
	SDLWindows window;

	if( !window.Init( DISPLAY_WIDTH, DISPLAY_HEIGHT ) )
	{
		fprintf( stderr, "ERROR::main - SDLWindows failed to initialize.\n" );
		window.Release();
		return 1;
	}

	window.Loop();

	window.Release();

	return 0;
}
