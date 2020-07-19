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
#include <fstream>

#include "common/configurations.h"
#include "common/gameinfo.h"
#include "engine/lifeengine.h"
#include "engine/ifactory.h"
#include "engine/iwindow.h"
#include "engine/iconcmd.h"
#include "engine/iscriptsystem.h"
#include "engine/ishaderfactory.h"
#include "engine/imaterialsystem.h"
#include "engine/iconvar.h"
#include "audio/iaudiosystem.h"
#include "audio/isound.h"
#include "audio/istreamsound.h"

#include "shaders/mytextshader.h"

#include "global.h"
#include "game.h"
#include "world.h"
#include "player.h"
#include "buildnum.h"

namespace scripts_api
{
#include "scripts_api/entites/prop_static.h"
}

#define REGISTER_FUNCTION( Function )		( scriptSystem->RegisterFunction( #Function, ( void* ) &Function ) )

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
// Load config
// ------------------------------------------------------------------------------------ //
void Game::LoadConfig( const std::string& Path )
{
	if ( !g_engine || !g_consoleSystem ) return;

	const le::GameInfo*		gameInfo = &g_engine->GetGameInfo();
	std::string				fullPath = std::string( gameInfo->gameDir ) + "/" + Path;
	std::ifstream			config( fullPath );
	
	if ( !config.is_open() )
	{
		std::ofstream			saveConfig( fullPath );
		le::Configurations		configurations = g_engine->GetConfigurations();

		// engine configures
		saveConfig << configurations.windowWidth->GetName() << " " << configurations.windowWidth->GetValueInt() << std::endl;
		saveConfig << configurations.windowHeight->GetName() << " " << configurations.windowHeight->GetValueInt() << std::endl;
		saveConfig << configurations.windowFullscreen->GetName() << " " << configurations.windowFullscreen->GetValueBool() << std::endl;
		saveConfig << configurations.mouseSensitivity->GetName() << " " << configurations.mouseSensitivity->GetValueFloat() << std::endl;
		saveConfig << configurations.rvsinc->GetName() << " " << configurations.rvsinc->GetValueBool() << std::endl;

		// game configures
		saveConfig << "bind w move_forward\n" <<
			"bind s move_backward\n" <<
			"bind a move_left\n" <<
			"bind d move_right\n" <<
			"bind shift sprint\n" <<
			"bind space jump\n"
			"bind e flashlight\n";

		g_consoleSystem->Exec( "bind w move_forward" );
		g_consoleSystem->Exec( "bind s move_backward" );
		g_consoleSystem->Exec( "bind a move_left" );
		g_consoleSystem->Exec( "bind d move_right" );
		g_consoleSystem->Exec( "bind shift sprint" );
		g_consoleSystem->Exec( "bind space jump" );
		g_consoleSystem->Exec( "bind e flashlight" );

		return;
	}

	config.close();
	g_consoleSystem->Exec( std::string( "exec " + Path ).c_str() );
}

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
		le::IScriptSystem*			scriptSystem = Engine->GetScriptSystem();

		Engine->GetMaterialSystem()->GetShaderFactory()->Register( MyTextShader::GetDescriptor() );
		g_consoleSystem->PrintInfo( "Eleot-Episodic build %i", Game_BuildNumber() );

		LoadConfig( "config.cfg" );

		// If engine in editor mode - it's all
		if ( g_engine->IsEditor() )		return true;

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

		// Register Game API for scripts
		using namespace			scripts_api;
		REGISTER_FUNCTION( PropStatic_Create );
		REGISTER_FUNCTION( PropStatic_Delete );
		REGISTER_FUNCTION( PropStatic_SetModel );

		input.Initialize();
		world = new World();
		if ( !world->LoadLevel( mapName ) )		throw std::runtime_error( "Level demo not loaded" );

		scr_test = g_resourceSystem->LoadScript( "test", "scripts/test.c" );
		if ( scr_test )
		{
			StartFn_t		startFn = ( StartFn_t ) scr_test->GetFunction( "Start" );
			update = ( UpdateFn_t ) scr_test->GetFunction( "Update" );
			if ( startFn )	startFn( world->GetLevel() );
		}

		music = g_resourceSystem->OpenStreamSound( "sounds/combine_harvester.ogg" );
		if ( music )
		{
			music->SetLoop( true );
			music->SetRelativeToListener( true );
			music->Play();
		}
	}
	catch ( const std::exception& Exception )
	{
		g_consoleSystem->PrintError( Exception.what() );
		return false;
	}

	return true;
}

// ------------------------------------------------------------------------------------ //
// Update game
// ------------------------------------------------------------------------------------ //
void Game::Update()
{
	// If engine in editor mode - exit from this method
	if ( g_engine->IsEditor() )		return;

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

	if ( music )
	{
		if ( g_inputSystem->IsKeyUp( le::BC_KEY_F4 ) )
			music->Play();

		if ( g_inputSystem->IsKeyUp( le::BC_KEY_F5 ) )
			music->Pause();

		if ( g_inputSystem->IsKeyUp( le::BC_KEY_F6 ) )
			music->Stop();
	}

	if ( g_inputSystem->IsKeyUp( le::BC_KEY_ESCAPE ) )
	{
		isShowingCursor = !isShowingCursor;
		g_window->SetShowCursor( isShowingCursor );
	}

	if ( update ) update();
	world->Update();
	input.ClearButtonsState();
}

// ------------------------------------------------------------------------------------ //
// Render game
// ------------------------------------------------------------------------------------ //
void Game::Render()
{
	world->Render();
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
	scr_test( nullptr ),
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
