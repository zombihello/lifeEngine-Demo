//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/igame.h"

//---------------------------------------------------------------------//

class Game : public le::IGame
{
public:
	// IGame
	virtual bool				Initialize( le::IEngine* Engine );
	virtual void				Update( le::UInt32_t DeltaTime );
	virtual void				OnEvent( const le::Event& Event );
};

//---------------------------------------------------------------------//