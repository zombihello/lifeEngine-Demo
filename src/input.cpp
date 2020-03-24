//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <memory.h>

#include "engine/ifactory.h"
#include "engine/iconcmd.h"

#include "global.h"
#include "game.h"
#include "input.h"

//---------------------------------------------------------------------//

le::IConCmd*			cmd_moveForward = nullptr;
le::IConCmd*			cmd_moveBackward = nullptr;
le::IConCmd*			cmd_moveLeft = nullptr;
le::IConCmd*			cmd_moveRight = nullptr;
le::IConCmd*			cmd_sprint = nullptr;
le::IConCmd*			cmd_jump = nullptr;

bool					buttons[ BT_COUNT ] = { false };

//---------------------------------------------------------------------//

// ------------------------------------------------------------------------------------ //
// Console command: move player forward
// ------------------------------------------------------------------------------------ //
void CMD_MoveForward( le::UInt32_t CountArguments, const char** Arguments )
{
	buttons[ BT_MOVE_FORWARD ] = true;
}

// ------------------------------------------------------------------------------------ //
// Console command: move player backward
// ------------------------------------------------------------------------------------ //
void CMD_MoveBackward( le::UInt32_t CountArguments, const char** Arguments )
{
	buttons[ BT_MOVE_BACKWARD ] = true;
}

// ------------------------------------------------------------------------------------ //
// Console command: move player left
// ------------------------------------------------------------------------------------ //
void CMD_MoveLeft( le::UInt32_t CountArguments, const char** Arguments )
{
	buttons[ BT_MOVE_LEFT ] = true;
}

// ------------------------------------------------------------------------------------ //
// Console command: move player right
// ------------------------------------------------------------------------------------ //
void CMD_MoveRight( le::UInt32_t CountArguments, const char** Arguments )
{
	buttons[ BT_MOVE_RIGHT ] = true;
}

// ------------------------------------------------------------------------------------ //
// Console command: sprint player while moving
// ------------------------------------------------------------------------------------ //
void CMD_Sprint( le::UInt32_t CountArguments, const char** Arguments )
{
	buttons[ BT_SPRINT ] = true;
}

// ------------------------------------------------------------------------------------ //
// Console command: jump player
// ------------------------------------------------------------------------------------ //
void CMD_Jump( le::UInt32_t CountArguments, const char** Arguments )
{
	buttons[ BT_JUMP ] = true;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Input::Input()
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Input::~Input()
{
	// Unregistering commands
	g_consoleSystem->UnregisterCommand( "move_forward" );
	g_consoleSystem->UnregisterCommand( "move_backward" );
	g_consoleSystem->UnregisterCommand( "move_left" );
	g_consoleSystem->UnregisterCommand( "move_right" );
	g_consoleSystem->UnregisterCommand( "sprint" );
	g_consoleSystem->UnregisterCommand( "jump" );
}

// ------------------------------------------------------------------------------------ //
// Intialize input game
// ------------------------------------------------------------------------------------ //
void Input::Initialize()
{
	le::IFactory*			factory = g_consoleSystem->GetFactory();

	// Creting objects console commands
	cmd_moveForward = ( le::IConCmd* ) factory->Create( CONCMD_INTERFACE_VERSION );
	cmd_moveBackward = ( le::IConCmd* ) factory->Create( CONCMD_INTERFACE_VERSION );
	cmd_moveLeft = ( le::IConCmd* ) factory->Create( CONCMD_INTERFACE_VERSION );
	cmd_moveRight = ( le::IConCmd* ) factory->Create( CONCMD_INTERFACE_VERSION );
	cmd_sprint = ( le::IConCmd* ) factory->Create( CONCMD_INTERFACE_VERSION );
	cmd_jump = ( le::IConCmd* ) factory->Create( CONCMD_INTERFACE_VERSION );

	// Initializing commands
	cmd_moveForward->Initialize( "move_forward", "Move player forward", CMD_MoveForward );
	cmd_moveBackward->Initialize( "move_backward", "Move player backward", CMD_MoveBackward);
	cmd_moveLeft->Initialize( "move_left", "Move player left", CMD_MoveLeft );
	cmd_moveRight->Initialize( "move_right", "Move player right", CMD_MoveRight );
	cmd_sprint->Initialize( "sprint", "Sprint player while moving", CMD_Sprint );
	cmd_jump->Initialize( "jump", "Jump player", CMD_Jump );

	// Registering commands
	g_consoleSystem->RegisterCommand( cmd_moveForward );
	g_consoleSystem->RegisterCommand( cmd_moveBackward );
	g_consoleSystem->RegisterCommand( cmd_moveLeft );
	g_consoleSystem->RegisterCommand( cmd_moveRight );
	g_consoleSystem->RegisterCommand( cmd_sprint );
	g_consoleSystem->RegisterCommand( cmd_jump );

	// Binding on keys commands for move player
	g_consoleSystem->Exec( "bind w move_forward" );
	g_consoleSystem->Exec( "bind s move_backward" );
	g_consoleSystem->Exec( "bind a move_left" );
	g_consoleSystem->Exec( "bind d move_right" );
	g_consoleSystem->Exec( "bind shift sprint" );
	g_consoleSystem->Exec( "bind space jump" );
}

// ------------------------------------------------------------------------------------ //
// Clear buttons state
// ------------------------------------------------------------------------------------ //
void Input::ClearButtonsState()
{
	memset( buttons, false, sizeof( bool ) * BT_COUNT );
}

// ------------------------------------------------------------------------------------ //
// Is button down
// ------------------------------------------------------------------------------------ //
bool Input::IsButtonDown( BUTTON_TYPE Type )
{
	return buttons[ Type ];
}
