//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "engine/lifeengine.h"
#include "engine/imodel.h"
#include "physics/ibody.h"

#include "entites/prop_static.h"
#include "global.h"
#include "game.h"
#include "world.h"
#include "player.h"
#include "hud.h"

#include "engine/iscript.h"
#include "engine/iscriptsystem.h"

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

	le::IMesh*		mesh = g_resourceSystem->LoadMesh( "axe", "models/axe.mdl" );
	if ( mesh )
	{
		le::IFactory*			factory = g_engine->GetFactory();
		le::IModel*				model = ( le::IModel* ) factory->Create( MODEL_INTERFACE_VERSION );
		if ( !model )			throw std::runtime_error( "le::IModel interface version[" MODEL_INTERFACE_VERSION "] not found in engine factory" );

		model->SetMesh( mesh );
		model->SetPosition( le::Vector3D_t( 0, 150, -55 ) );
		model->SetScale( le::Vector3D_t( 50, 50, 50 ) );
		model->SetRotation( le::Vector3D_t( glm::radians(90.f), 0, 0 ) );
		model->Rotate( le::Vector3D_t( 0, glm::radians(24.f), 0 ) );

		/*le::ICollider*			collider = g_resourceSystem->LoadCollider( "axe", "models/axe.phy" );
		le::IBody*				body = nullptr;
		if ( collider )
		{
			body = ( le::IBody* ) g_physicsSystem->GetFactory()->Create( BODY_INTERFACE_VERSION );
			body->Create( collider, 10, le::Vector3D_t( 0.f, 0.f, 0.f ), false );
			body->SetPosition( model->GetPosition() );
			body->SetRotation( model->GetRotation() );
			g_physicsSystem->AddBody( body );
		}*/

		Prop_Static*	propModel = new Prop_Static();
		propModel->SetModel( model, nullptr );
		propModel->SetLevel( level );
		level->AddEntity( propModel );
	}

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
// Update world
// ------------------------------------------------------------------------------------ //
void World::Update()
{	
	player->Update();
	level->Update();
}

// ------------------------------------------------------------------------------------ //
// Render world
// ------------------------------------------------------------------------------------ //
void World::Render()
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
