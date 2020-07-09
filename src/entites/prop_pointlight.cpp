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
#include "prop_pointlight.h"

// ------------------------------------------------------------------------------------ //
// Set property entity
// ------------------------------------------------------------------------------------ //
void Prop_PointLight::KeyValue( const char* Key, const char* Value )
{}

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Prop_PointLight::Update()
{}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void Prop_PointLight::Render( le::IStudioRender* StudioRender )
{
	if ( !pointLight ) return;
	StudioRender->SubmitLight( pointLight );
}

// ------------------------------------------------------------------------------------ //
// Set model
// ------------------------------------------------------------------------------------ //
void Prop_PointLight::SetModel( le::IModel* Model, le::IBody* Body )
{}

// ------------------------------------------------------------------------------------ //
// Set position
// ------------------------------------------------------------------------------------ //
void Prop_PointLight::SetPosition( const le::Vector3D_t& Position )
{
	if ( pointLight ) pointLight->SetPosition( Position );
	position = Position;
}

// ------------------------------------------------------------------------------------ //
// Is visible
// ------------------------------------------------------------------------------------ //
bool Prop_PointLight::IsVisible(le::ICamera* Camera) const
{
	if ( !pointLight ) return false;
	return Camera->IsVisible( pointLight->GetPosition(), pointLight->GetRadius() );
}

// ------------------------------------------------------------------------------------ //
// Get center
// ------------------------------------------------------------------------------------ //
le::Vector3D_t Prop_PointLight::GetCenter() const
{
	if ( !pointLight ) return position;
	return pointLight->GetPosition();
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Prop_PointLight::Prop_PointLight() :
	pointLight( nullptr )
{
	pointLight = ( le::IPointLight* ) g_studioRender->GetFactory()->Create( POINTLIGHT_INTERFACE_VERSION );
	pointLight->SetColor( le::Vector4D_t( 1, 1, 1, 1 ) );
	pointLight->SetRadius( 250 );
	pointLight->SetIntensivity( 11400 );
	pointLight->SetPosition( position );
}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Prop_PointLight::~Prop_PointLight()
{
	if ( pointLight )
	{
		if ( pointLight->GetCountReferences() <= 1 )
			pointLight->Release();
		else
			pointLight->DecrementReference();
	}
}
