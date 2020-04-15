//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef API_PROP_STATIC_H
#define API_PROP_STATIC_H

#include "engine/model.h"
#include "physics/body.h"

//---------------------------------------------------------------------//

typedef void*			ent_propStatic_t;

//---------------------------------------------------------------------//

/* Create prop static */
extern ent_propStatic_t				PropStatic_Create();

/* Delete prop static */
extern void							PropStatic_Delete( ent_propStatic_t Object );

/* Set model */
extern void							PropStatic_SetModel( ent_propStatic_t Object, model_t Model, body_t Body );

//---------------------------------------------------------------------//

#endif // API_PROP_STATIC_H
