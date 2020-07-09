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

#include "engine/ifactory.h"
#include "engine/icamera.h"
#include "engine/imodel.h"
#include "engine/iresourcesystem.h"
#include "engine/scriptdescriptor.h"
#include "studiorender/istudiorender.h"
#include "physics/ibody.h"
#include "studiorender/istudiorender.h"

#include "../global.h"
#include "../world.h"
#include "prop_directionallight.h"

// ------------------------------------------------------------------------------------ //
// Set property entity
// ------------------------------------------------------------------------------------ //
void Prop_DirectionalLight::KeyValue( const char* Key, const char* Value )
{}

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Prop_DirectionalLight::Update()
{}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void Prop_DirectionalLight::Render( le::IStudioRender* StudioRender )
{
	if ( !directionalLight ) return;
	StudioRender->SubmitLight( directionalLight );
}

// ------------------------------------------------------------------------------------ //
// Set model
// ------------------------------------------------------------------------------------ //
void Prop_DirectionalLight::SetModel( le::IModel* Model, le::IBody* Body )
{}

// ------------------------------------------------------------------------------------ //
// Set position
// ------------------------------------------------------------------------------------ //
void Prop_DirectionalLight::SetPosition( const le::Vector3D_t& Position )
{
	position = Position;
}

// ------------------------------------------------------------------------------------ //
// Is visible
// ------------------------------------------------------------------------------------ //
bool Prop_DirectionalLight::IsVisible(le::ICamera* Camera) const
{
	return true;
}

// ------------------------------------------------------------------------------------ //
// Get center
// ------------------------------------------------------------------------------------ //
le::Vector3D_t Prop_DirectionalLight::GetCenter() const
{
	return position;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Prop_DirectionalLight::Prop_DirectionalLight() :
	directionalLight( nullptr )
{
	directionalLight = ( le::IDirectionalLight* ) g_studioRender->GetFactory()->Create( DIRECTIONALLIGHT_INTERFACE_VERSION );
	directionalLight->SetColor( le::Vector4D_t( 1, 1, 1, 1 ) );
	directionalLight->SetDirection( le::Vector3D_t( -10.f, 5.f, 0.f ) );
	directionalLight->SetIntensivity( 1 );
}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Prop_DirectionalLight::~Prop_DirectionalLight()
{
	if ( directionalLight )
	{
		if ( directionalLight->GetCountReferences() <= 1 )
			directionalLight->Release();
		else
			directionalLight->DecrementReference();
	}
}
