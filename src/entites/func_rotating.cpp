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
#include "func_rotating.h"

#define			DEFAULT_SPEED			0.03f

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Func_Rotating::Update()
{
	if ( !model ) return;

	model->Rotate( le::Vector3D_t( 0, speed, 0 ) );
	body->SetRotation( model->GetRotation() );
}

// ------------------------------------------------------------------------------------ //
// Set values
// ------------------------------------------------------------------------------------ //
void Func_Rotating::KeyValue( const char* Key, const char* Value )
{
	if ( strcmp( Key, "Speed" ) == 0 )
		speed = StringToNumber< float >( Value, DEFAULT_SPEED );
	else if ( strcmp( Key, "origin" ) == 0 )
	{
		position = StringToVector3D( Value );
		if ( model ) model->SetPosition( position );
		if ( body ) body->SetPosition( position );
	}
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Func_Rotating::Func_Rotating():
	speed( DEFAULT_SPEED ),
	model( nullptr ),
	body( nullptr )
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

	if ( body )
	{
		g_physicsSystem->RemoveBody( body );
		if ( body->GetCountReferences() <= 1 )			body->Release();
		else											body->DecrementReference();
	}
}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void Func_Rotating::Render( le::IStudioRender* StudioRender )
{
	if ( !model ) return;
	StudioRender->SubmitModel( model, model->GetStartFace(), model->GetCountFace() );
}

// ------------------------------------------------------------------------------------ //
// Set model
// ------------------------------------------------------------------------------------ //
void Func_Rotating::SetModel( le::IModel* Model, le::IBody* Body )
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
// Is visible
// ------------------------------------------------------------------------------------ //
bool Func_Rotating::IsVisible( le::ICamera* Camera ) const
{
	if ( !model ) return false;
	return Camera->IsVisible( model->GetMin(), model->GetMax() );
}

// ------------------------------------------------------------------------------------ //
// Get center
// ------------------------------------------------------------------------------------ //
le::Vector3D_t Func_Rotating::GetCenter() const
{
	if ( !model ) return position;
	return ( model->GetMax() + model->GetMin() ) / 2.f;
}
