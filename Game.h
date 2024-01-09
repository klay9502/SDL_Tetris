#ifndef __GAME_H__
#define __GAME_H__

class Game
{
public:
	Game( void );
	~Game( void );

	bool Init( void );
	void Update( void );
	void Release( void );
};

#endif __GAME_H__