//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <vector>

#include "engine/icamera.h"
#include "engine/imodel.h"
#include "engine/iresourcesystem.h"
#include "engine/scriptdescriptor.h"
#include "studiorender/istudiorender.h"
#include "physics/ibody.h"

#include "../global.h"
#include "../world.h"
#include "prop_static.h"

// ------------------------------------------------------------------------------------ //
// Set property entity
// ------------------------------------------------------------------------------------ //
void Prop_Static::KeyValue( const char* Key, const char* Value )
{}

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Prop_Static::Update()
{
	if ( body && !body->IsStatic() )
	{
		body->Activate();
		model->SetPosition( body->GetPosition() );
		model->SetRotation( body->GetRotation() );
	}
}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void Prop_Static::Render( le::IStudioRender* StudioRender )
{
	if ( !model ) return;
	StudioRender->SubmitModel( model );
}

// ------------------------------------------------------------------------------------ //
// Set model
// ------------------------------------------------------------------------------------ //
void Prop_Static::SetModel( le::IModel* Model, le::IBody* Body )
{
	model = Model;
	body = Body;

	if ( model ) model->IncrementReference();
	if ( body ) body->IncrementReference();
}

// ------------------------------------------------------------------------------------ //
// Is visible
// ------------------------------------------------------------------------------------ //
bool Prop_Static::IsVisible(le::ICamera* Camera) const
{
	if ( !model ) return false;
	return Camera->IsVisible( model->GetMin(), model->GetMax() );
}

// ------------------------------------------------------------------------------------ //
// Get center
// ------------------------------------------------------------------------------------ //
le::Vector3D_t Prop_Static::GetCenter() const
{
	if ( !model ) return position;
	return ( model->GetMin() + model->GetMax() ) / 2.f;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Prop_Static::Prop_Static() :
	model( nullptr ),
	body( nullptr )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Prop_Static::~Prop_Static()
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
		if ( body->GetCountReferences() <= 1 )
			body->Release();
		else
			body->DecrementReference();
	}
}
