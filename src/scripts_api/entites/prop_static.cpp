//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "entites/prop_static.h"
#include "physics/ibody.h"

namespace scripts_api
{
#include "prop_static.h"
}

#define ENTITY( Object )		( static_cast< Prop_Static* >( Object ) )

// ------------------------------------------------------------------------------------ //
// Create prop static
// ------------------------------------------------------------------------------------ //
scripts_api::ent_propStatic_t scripts_api::PropStatic_Create()
{
	return new Prop_Static();
}

// ------------------------------------------------------------------------------------ //
// Delete prop static
// ------------------------------------------------------------------------------------ //
void scripts_api::PropStatic_Delete( ent_propStatic_t Object )
{
	if ( !Object ) return;

	if ( ENTITY( Object )->GetCountReferences() <= 1 )
		ENTITY( Object )->Release();
	else
		ENTITY( Object )->DecrementReference();

	Object = nullptr;
}

// ------------------------------------------------------------------------------------ //
// Set model
// ------------------------------------------------------------------------------------ //
void scripts_api::PropStatic_SetModel( ent_propStatic_t Object, model_t Model, body_t Body )
{
	if ( !Object || !Model ) return;
	ENTITY( Object )->SetModel( ( le::IModel* ) Model, ( le::IBody* ) Body );
}
