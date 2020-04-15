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
		body->SetRotation( model->GetRotation() );
	}
	else if ( isClose && donePercentag > 0.f )
	{
		donePercentag = glm::max( 0.f, donePercentag - speedClose );
		model->SetRotation( glm::slerp( startRotation, endRotation, donePercentag ) );
		body->SetRotation( model->GetRotation() );
	}
}

// ------------------------------------------------------------------------------------ //
// Set values
// ------------------------------------------------------------------------------------ //
void Func_Door::KeyValue( const char* Key, const char* Value )
{
	if ( strcmp( Key, "origin" ) == 0 )
	{
		position = StringToVector3D( Value );
		if ( model ) model->SetPosition( position );
		if ( body ) body->SetPosition( position );
	}
	else if ( strcmp( Key, "AngleMax" ) == 0 )
	{
		angleMax = StringToNumber< float >( Value, DEFAULT_ANGLE_MAX );
		endRotation = le::Quaternion_t( le::Vector3D_t( 0.f, glm::radians( angleMax ), 0.f ) );
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
	isOpen( false ),
	isClose( true ),
	model( nullptr ),
	body( nullptr ),
	donePercentag( 0.f ),
	angleMax( DEFAULT_ANGLE_MAX ),
	speedOpen( DEFAULT_SPEED_OPEN ),
	speedClose( DEFAULT_SPEED_CLOSE ),
	startRotation( le::Vector3D_t( 0.f, 0.f, 0.f ) ),
	endRotation( le::Vector3D_t( 0.f, glm::radians( angleMax ), 0.f ) )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Func_Door::~Func_Door()
{
	if ( model )
	{
		if ( model->GetCountReferences() <= 1 )
			model->Release();
		else
			model->DecrementReference();
	}

	if ( body )
	{
		g_physicsSystem->RemoveBody( body );

		if ( body->GetCountReferences() <= 1 )
			body->Release();
		else
			body->DecrementReference();
	}
}

// ------------------------------------------------------------------------------------ //
// Render entity
// ------------------------------------------------------------------------------------ //
void Func_Door::Render( le::IStudioRender* StudioRender )
{
	if ( !model ) return;
	StudioRender->SubmitMesh( model->GetMesh(), model->GetTransformation(), model->GetStartFace(), model->GetCountFace() );
}

// ------------------------------------------------------------------------------------ //
// Set entity model
// ------------------------------------------------------------------------------------ //
void Func_Door::SetModel( le::IModel* Model, le::IBody* Body )
{
	model = Model;
	body = Body;

	if ( model )
	{
		model->IncrementReference();
		model->SetPosition( position );
	}

	if ( body )
	{
		body->IncrementReference();
		body->SetPosition( position );
	}
}

// ------------------------------------------------------------------------------------ //
// Is entity visible
// ------------------------------------------------------------------------------------ //
bool Func_Door::IsVisible( le::ICamera* Camera ) const
{
	if ( !model ) return false;
	return Camera->IsVisible( model->GetMin(), model->GetMax() );
}

// ------------------------------------------------------------------------------------ //
// Get center entity
// ------------------------------------------------------------------------------------ //
le::Vector3D_t Func_Door::GetCenter() const
{
	if ( !model ) return position;
	return ( model->GetMax() + model->GetMin() ) / 2.f;
}
