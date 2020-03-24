//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include "engine/igame.h"

#include "gamefactory.h"
#include "input.h"
#include "tsingleton.h"

//---------------------------------------------------------------------//

class World;

//---------------------------------------------------------------------//

class Game : public le::IGame, public TSingleton< Game >
{
public:
	// IGame
	virtual bool			Initialize( le::IEngine* Engine, le::UInt32_t CountArguments, const char** Arguments );
	virtual void			FixedUpdate();
	virtual void			Update();
	virtual void			OnEvent( const le::Event& Event );

	// Game
	Game();
	~Game();

	inline GameFactory*		GetFactory()	{ return &gameFactory; }	

private:
	bool			isDebugMode;
	bool			isShowingGBuffer;
	bool			isEnablePhysicsDebug;
	bool			isShowingCursor;

	GameFactory		gameFactory;
	Input			input;

	World*			world;	
};

//---------------------------------------------------------------------//

#endif // !GAME_H
