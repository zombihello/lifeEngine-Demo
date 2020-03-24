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
#include "func_rotating.h"

#define			DEFAULT_SPEED			0.03f

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Func_Rotating::Update()
{
	if ( !model ) return;
	if ( isNeedUpdatePosition )
	{
		model->SetPosition( position );
		isNeedUpdatePosition = false;
	}

	model->Rotate( le::Vector3D_t( 0, speed, 0 ) );
}

// ------------------------------------------------------------------------------------ //
// Set values
// ------------------------------------------------------------------------------------ //
void Func_Rotating::KeyValue( const char* Key, const char* Value )
{
	if ( level && strcmp( Key, "model" ) == 0 )
	{
		int			idModel = StringToNumber< int >( Value, -1 );
		if ( idModel == -1 )		return;

		model = level->GetModel( idModel );
		if ( model ) model->IncrementReference();
	}
	else if ( strcmp( Key, "Speed" ) == 0 )
		speed = StringToNumber< float >( Value, DEFAULT_SPEED );
	else if ( strcmp( Key, "origin" ) == 0 )
	{
		position = StringToVector3D( Value );
		isNeedUpdatePosition = true;
	}
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Func_Rotating::Func_Rotating():
	isNeedUpdatePosition( false ),
	model( nullptr ),
	speed( DEFAULT_SPEED )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Func_Rotating::~Func_Rotating()
{
	if ( model )
	{
		if ( model->GetCountReferences() <= 1 )			model->Release();
		else											model->DecrementReference();
	}
}
