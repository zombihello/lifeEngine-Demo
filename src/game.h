//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// Репозиторий игры:	https://github.com/zombihello/Eleot-Episodic
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/igame.h"

//---------------------------------------------------------------------//

class Game : public le::IGame
{
public:
	virtual bool				Initialize( le::IEngine* Engine );
	virtual void				Update( le::UInt32_t DeltaTime );
	virtual void				OnEvent( const le::Event& Event );
};

//---------------------------------------------------------------------//