//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/ilevel.h"

#include "../global.h"
#include "func_door.h"

#define			DEFAULT_ANGLE_MAX			90.f
#define			DEFAULT_SPEED_OPEN			0.03f
#define			DEFAULT_SPEED_CLOSE			0.03f

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Func_Door::Update()
{
	if ( !model ) return;

	if ( isNeedUpdate )
	{
		model->SetPosition( position );
		startRotation = le::Quaternion_t( le::Vector3D_t( 0.f, 0.f, 0.f ) );
		endRotation = le::Quaternion_t( le::Vector3D_t( 0.f, glm::radians( angleMax ), 0.f ) );
		isNeedUpdate = false;
	}

	// This test code. In releale mast be deleted
	if ( g_inputSystem->IsKeyDown( le::BC_KEY_F ) )
	{
		isOpen = true;
		isClose = false;
	}
	else if ( g_inputSystem->IsKeyUp( le::BC_KEY_F ) && isOpen )
	{
		isOpen = false;
		isClose = true;
	}

	if ( isOpen && donePercentag < 1.f )
	{
		donePercentag = glm::min( 1.f, donePercentag + speedOpen );
		model->SetRotation( glm::slerp( startRotation, endRotation, donePercentag ) );
	}
	else if ( isClose && donePercentag > 0.f )
	{
		donePercentag = glm::max( 0.f, donePercentag - speedClose );
		model->SetRotation( glm::slerp( startRotation, endRotation, donePercentag ) );
	}
}

// ------------------------------------------------------------------------------------ //
// Set values
// ------------------------------------------------------------------------------------ //
void Func_Door::KeyValue( const char* Key, const char* Value )
{
	if ( level && strcmp( Key, "model" ) == 0 )
	{
		int			idModel = StringToNumber< int >( Value, -1 );
		if ( idModel == -1 )		return;

		model = level->GetModel( idModel );
		if ( model ) model->IncrementReference();
	}
	else if ( strcmp( Key, "origin" ) == 0 )
	{
		position = StringToVector3D( Value );
		isNeedUpdate = true;
	}
	else if ( strcmp( Key, "AngleMax" ) == 0 )
	{
		angleMax = StringToNumber< float >( Value, DEFAULT_ANGLE_MAX );
		isNeedUpdate = true;
	}
	else if ( strcmp( Key, "SpeedOpen" ) == 0 )
		speedOpen = StringToNumber< float >( Value, DEFAULT_SPEED_OPEN );
	else if ( strcmp( Key, "SpeedClose" ) == 0 )
		speedClose = StringToNumber< float >( Value, DEFAULT_SPEED_CLOSE );
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Func_Door::Func_Door() :
	isNeedUpdate( false ),
	isOpen( false ),
	isClose( true ),
	model( nullptr ),
	donePercentag( 0.f ),
	angleMax( DEFAULT_ANGLE_MAX ),
	speedOpen( DEFAULT_SPEED_OPEN ),
	speedClose( DEFAULT_SPEED_CLOSE )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Func_Door::~Func_Door()
{
	if ( model )
	{
		if ( model->GetCountReferences() <= 1 )			model->Release();
		else											model->DecrementReference();
	}
}
