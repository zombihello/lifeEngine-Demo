//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

#include "engine/ifactory.h"

//---------------------------------------------------------------------//

class GameFactory : public le::IFactory
{
public:
	// IFactory
	virtual void*			Create( const char* NameInterface );
	virtual void			Delete( void* Object );
};

//---------------------------------------------------------------------//

#endif // !GAME_FACTORY_H
