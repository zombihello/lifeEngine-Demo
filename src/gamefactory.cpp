//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "gamefactory.h"
#include "entites/info_player_start.h"
#include "entites/func_rotating.h"
#include "entites/func_door.h"

// ------------------------------------------------------------------------------------ //
// Create game object
// ------------------------------------------------------------------------------------ //
void* GameFactory::Create( const char* NameInterface )
{
	if ( strcmp( "info_player_start", NameInterface ) == 0 )			return new Info_Player_Start();
	else if ( strcmp( "func_rotating", NameInterface ) == 0 )			return new Func_Rotating();
	else if ( strcmp( "func_door", NameInterface ) == 0 )				return new Func_Door();

	return nullptr;
}

// ------------------------------------------------------------------------------------ //
// Delete game object
// ------------------------------------------------------------------------------------ //
void GameFactory::Delete( void* Object )
{
	if ( !Object ) return;
	delete Object;
}
