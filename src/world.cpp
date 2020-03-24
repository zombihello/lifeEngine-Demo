//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/lifeengine.h"

#include "global.h"
#include "game.h"
#include "world.h"
#include "player.h"
#include "hud.h"

// ------------------------------------------------------------------------------------ //
// Load level
// ------------------------------------------------------------------------------------ //

bool World::LoadLevel( const std::string& MapName )
{
	UnloadLevel();

	level = g_resourceSystem->LoadLevel( "level", ( std::string( "maps/" ) + MapName + ".bsp" ).c_str(), Game::GetInstance()->GetFactory() );
	if ( !level ) 	return false;

	player = new Player();
	hud = new HUD();

	player->Initialize();
	hud->Initialize();

	level->AddCamera( player->GetCamera() );
	level->IncrementReference();
	return true;
}

// ------------------------------------------------------------------------------------ //
// Unload level
// ------------------------------------------------------------------------------------ //
void World::UnloadLevel()
{
	if ( level )
	{
		level->DecrementReference();
		g_resourceSystem->UnloadLevel( "level" );
		delete hud;
		delete player;
	}
}

// ------------------------------------------------------------------------------------ //
// Fixed update world
// ------------------------------------------------------------------------------------ //
void World::FixedUpdate()
{
	player->Update();
	level->Update();
}

// ------------------------------------------------------------------------------------ //
// Update world
// ------------------------------------------------------------------------------------ //
void World::Update()
{
	level->Render();
	hud->Render();
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
World::World() :
	level( nullptr ),
	player( nullptr ),
	hud( nullptr )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
World::~World()
{
	UnloadLevel();
}
