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
#include "prop_spotlight.h"

// ------------------------------------------------------------------------------------ //
// Set property entity
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::KeyValue( const char* Key, const char* Value )
{}

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::Update()
{}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::Render( le::IStudioRender* StudioRender )
{
	if ( !spotLight ) return;
	StudioRender->SubmitLight( spotLight );
}

// ------------------------------------------------------------------------------------ //
// Set model
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetModel( le::IModel* Model, le::IBody* Body )
{}

// ------------------------------------------------------------------------------------ //
// Set position
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetPosition( const le::Vector3D_t& Position )
{
	if ( spotLight ) spotLight->SetPosition( Position );
	position = Position;
}

// ------------------------------------------------------------------------------------ //
// Is visible
// ------------------------------------------------------------------------------------ //
bool Prop_SpotLight::IsVisible(le::ICamera* Camera) const
{
	if ( !spotLight ) return false;
	return true;
}

// ------------------------------------------------------------------------------------ //
// Get center
// ------------------------------------------------------------------------------------ //
le::Vector3D_t Prop_SpotLight::GetCenter() const
{
	if ( !spotLight ) return position;
	return spotLight->GetPosition();
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Prop_SpotLight::Prop_SpotLight() :
	spotLight( nullptr )
{
	spotLight = ( le::ISpotLight* ) g_studioRender->GetFactory()->Create( SPOTLIGHT_INTERFACE_VERSION );
}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Prop_SpotLight::~Prop_SpotLight()
{
	if ( spotLight )
	{
		if ( spotLight->GetCountReferences() <= 0 )
			spotLight->Release();
		else
			spotLight->DecrementReference();
	}
}

// ------------------------------------------------------------------------------------ //
// Set rotation
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetRotation( const le::Quaternion_t& Quaternion )
{
	if ( !spotLight ) return;
	spotLight->SetRotation( Quaternion );
}

// ------------------------------------------------------------------------------------ //
// Set radius
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetRadius( float Radius )
{
	if ( !spotLight ) return;
	spotLight->SetRadius( Radius );
}

// ------------------------------------------------------------------------------------ //
// Set height
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetHeight( float Height )
{
	if ( !spotLight ) return;
	spotLight->SetHeight( Height );
}

// ------------------------------------------------------------------------------------ //
// Set color
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetColor( const le::Vector4D_t& Color )
{
	if ( !spotLight ) return;
	spotLight->SetColor( Color );
}

// ------------------------------------------------------------------------------------ //
// Set specular
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetSpecular( const le::Vector4D_t& Color )
{
	if ( !spotLight ) return;
	spotLight->SetSpecular( Color );
}

// ------------------------------------------------------------------------------------ //
// Set intensivity
// ------------------------------------------------------------------------------------ //
void Prop_SpotLight::SetIntensivity( float Intensivity )
{
	if ( !spotLight ) return;
	spotLight->SetIntensivity( Intensivity );
}

// ------------------------------------------------------------------------------------ //
// Get color
// ------------------------------------------------------------------------------------ //
const le::Vector4D_t Prop_SpotLight::GetColor() const
{
	if ( !spotLight )		return le::Vector4D_t( 0.f, 0.f, 0.f, 0.f );
	return spotLight->GetColor();
}

// ------------------------------------------------------------------------------------ //
// Get specular
// ------------------------------------------------------------------------------------ //
const le::Vector4D_t Prop_SpotLight::GetSpecular() const
{
	if ( !spotLight )		return le::Vector4D_t( 0.f, 0.f, 0.f, 0.f );
	return spotLight->GetSpecular();
}

// ------------------------------------------------------------------------------------ //
// Get intensivity
// ------------------------------------------------------------------------------------ //
float Prop_SpotLight::GetIntensivity() const
{
	if ( !spotLight )		return 0.f;
	return spotLight->GetIntensivity();
}

// ------------------------------------------------------------------------------------ //
// Get rotation
// ------------------------------------------------------------------------------------ //
const le::Quaternion_t Prop_SpotLight::GetRotation() const
{
	if ( !spotLight )		return le::Quaternion_t( 0.f, 0.f, 0.f, 0.f );
	return spotLight->GetRotation();
}

// ------------------------------------------------------------------------------------ //
// Get radius
// ------------------------------------------------------------------------------------ //
float Prop_SpotLight::GetRadius() const
{
	if ( !spotLight )		return 0.f;
	return spotLight->GetRadius();
}

// ------------------------------------------------------------------------------------ //
// Get haight
// ------------------------------------------------------------------------------------ //
float Prop_SpotLight::GetHeight() const
{
	if ( !spotLight )		return 0.f;
	return spotLight->GetHeight();
}
