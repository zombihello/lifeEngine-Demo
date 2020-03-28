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
#include <string>
#include <exception>
#include <stdexcept>

#include "engine/lifeengine.h"
#include "engine/ifactory.h"
#include "engine/iwindow.h"
#include "engine/iconcmd.h"

#include "global.h"
#include "game.h"
#include "world.h"
#include "player.h"
#include "buildnum.h"

//---------------------------------------------------------------------//

bool					isEnabledNoclip = false;
le::IConCmd*			cmd_noclip = nullptr;

//---------------------------------------------------------------------//

// ------------------------------------------------------------------------------------ //
// Console command: noclip
// ------------------------------------------------------------------------------------ //
void CMD_Noclip( le::UInt32_t CountArguments, const char** Arguments )
{
	Player*			player = Player::GetInstance();
	isEnabledNoclip = !isEnabledNoclip;

	if ( player )
		player->SetCameraType( isEnabledNoclip ? CT_FLY : CT_PHYSICS );
}

LIFEENGINE_GAME_API( Game )

// ------------------------------------------------------------------------------------ //
// Initialize game
// ------------------------------------------------------------------------------------ //
bool Game::Initialize( le::IEngine* Engine, le::UInt32_t CountArguments, const char** Arguments )
{
	try
	{
		g_engine = Engine;
		g_consoleSystem = Engine->GetConsoleSystem();
		g_inputSystem = Engine->GetInputSystem();
		g_studioRender = Engine->GetStudioRender();
		g_window = Engine->GetWindow();
		g_resourceSystem = Engine->GetResourceSystem();
		g_physicsSystem = Engine->GetPhysicsSystem();

		g_consoleSystem->PrintInfo( "Eleot-Episodic build %i", Game_BuildNumber() );

		isShowingCursor = false;
		g_window->SetShowCursor( isShowingCursor );

		std::string				mapName = "demo";
		for ( int index = 0; index < CountArguments; ++index )
		{
			if ( strstr( Arguments[ index ], "-map" ) && index + 1 < CountArguments )
			{
				mapName = Arguments[ index + 1 ];
				++index;
			}
			else if ( strstr( Arguments[ index ], "-dev" ) || strstr( Arguments[ index ], "-debug" ) )
				isDebugMode = true;
		}

		// Initialize console commands
		le::IFactory*			consoleSystemFactory = g_consoleSystem->GetFactory();
		cmd_noclip = ( le::IConCmd* ) consoleSystemFactory->Create( CONCMD_INTERFACE_VERSION );
		if ( !cmd_noclip )		throw std::runtime_error( "le::IConCmd interface version[" CONCMD_INTERFACE_VERSION "] not found in console system factory" );

		cmd_noclip->Initialize( "noclip", "Enabled fly mode", CMD_Noclip );
		g_consoleSystem->RegisterCommand( cmd_noclip );

		input.Initialize();
		world = new World();
		if ( !world->LoadLevel( mapName ) )		throw std::runtime_error( "Level demo not loaded" );
	}
	catch ( const std::exception& Exception )
	{
		g_consoleSystem->PrintError( Exception.what() );
		return false;
	}

	return true;
}

// ------------------------------------------------------------------------------------ //
// Fixed update game
// ------------------------------------------------------------------------------------ //
void Game::FixedUpdate()
{
	world->FixedUpdate();
	input.ClearButtonsState();
}

// ------------------------------------------------------------------------------------ //
// Update game
// ------------------------------------------------------------------------------------ //
void Game::Update()
{
	// This code is temp. Mast be deleted when created gui console
	if ( isDebugMode )
	{
		if ( g_inputSystem->IsKeyUp( le::BC_KEY_F1 ) )
		{
			isEnablePhysicsDebug = !isEnablePhysicsDebug;
			g_consoleSystem->Exec( ( std::string( "phy_debug " ) + std::to_string( isEnablePhysicsDebug ) ).c_str() );
		}

		if ( g_inputSystem->IsKeyUp( le::BC_KEY_F2 ) )
		{
			isShowingGBuffer = !isShowingGBuffer;
			g_consoleSystem->Exec( ( std::string( "r_showgbuffer " ) + std::to_string( isShowingGBuffer ) ).c_str() );
		}

		if ( g_inputSystem->IsKeyUp( le::BC_KEY_F3 ) )
		{
			Player*			player = Player::GetInstance();
			isEnabledNoclip = !isEnabledNoclip;

			if ( player )
				player->SetCameraType( isEnabledNoclip ? CT_FLY : CT_PHYSICS );
		}
	}

	if ( g_inputSystem->IsKeyUp( le::BC_KEY_ESCAPE ) )
	{
		isShowingCursor = !isShowingCursor;
		g_window->SetShowCursor( isShowingCursor );
	}

	world->Update();
}

// ------------------------------------------------------------------------------------ //
// Event handler
// ------------------------------------------------------------------------------------ //
void Game::OnEvent( const le::Event& Event )
{}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Game::Game() :
	world( nullptr ),
	isDebugMode( false ),
	isShowingGBuffer( false ),
	isEnablePhysicsDebug( false ),
	isShowingCursor( true )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Game::~Game()
{
	if ( world )		delete world;
	g_consoleSystem->UnregisterCommand( "noclip" );
}
