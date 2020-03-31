//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// �����������:		https://github.com/zombihello/Eleot-Episodic/
// ������:			���� �������� (zombiHello)
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
	virtual void					KeyValue( const char* Key, const char* Value );
	virtual void					Update();	
	virtual void					Render( le::IStudioRender* StudioRender );

	virtual void					SetModel( le::IModel* Model, le::IBody* Body );

	virtual bool					IsVisible( le::ICamera* Camera ) const;
};

//---------------------------------------------------------------------//

#endif // !INFO_PLAYER_START_H

