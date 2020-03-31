//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/icamera.h"
#include "engine/imodel.h"
#include "studiorender/istudiorender.h"
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
{}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void Prop_Static::Render( le::IStudioRender* StudioRender )
{
	if ( !model ) return;
	StudioRender->SubmitMesh( model->GetMesh(), model->GetTransformation() );
}

// ------------------------------------------------------------------------------------ //
// Set model
// ------------------------------------------------------------------------------------ //
void Prop_Static::SetModel( le::IModel* Model, le::IBody* Body )
{
	model = Model;
	if ( model ) model->IncrementReference();
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
	model( nullptr )
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
}
