//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef WORLD_H
#define WORLD_H

#include <string>

#include "engine/ilevel.h"
#include "tsingleton.h"

//---------------------------------------------------------------------//

class Player;
class HUD;

//---------------------------------------------------------------------//

class World : public TSingleton< World >
{
public:
	World();
	~World();

	bool			LoadLevel( const std::string& MapName );
	void			UnloadLevel();
	void			Update();
	void			Render();

private:
	le::ILevel*		level;
	Player*			player;
	HUD*			hud;
};

//---------------------------------------------------------------------//

#endif // !WORLD_H
