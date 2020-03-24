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

#include "engine/ilevel.h"
#include "../player.h"
#include "info_player_start.h"

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Info_Player_Start::Update()
{
	Player::GetInstance()->SetPosition( position );
	level->RemoveEntity( this );
	delete this;
}

// ------------------------------------------------------------------------------------ //
// Set values
// ------------------------------------------------------------------------------------ //
void Info_Player_Start::KeyValue( const char* Key, const char* Value )
{
	if ( strcmp( Key, "origin" ) == 0 )
		position = StringToVector3D( Value );
}
