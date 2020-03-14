//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
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
	virtual void					Update( le::UInt32_t DeltaTime );
	virtual void					KeyValue( const char* Key, const char* Value );
};

//---------------------------------------------------------------------//

#endif // !INFO_PLAYER_START_H

