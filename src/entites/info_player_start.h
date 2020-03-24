//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef INFO_PLAYER_START_H
#define INFO_PLAYER_START_H

#include "baseentity.h"

//---------------------------------------------------------------------//

class Info_Player_Start : public BaseEntity
{
public:
	// IEntity
	virtual void					Update();
	virtual void					KeyValue( const char* Key, const char* Value );
};

//---------------------------------------------------------------------//

#endif // !INFO_PLAYER_START_H

