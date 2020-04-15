#include <engine/consolesystem.h>
#include <engine/inputsystem.h>
#include <engine/model.h>
#include <engine/resourcesystem.h>
#include <engine/engine.h>
#include <engine/camera.h>
#include <engine/level.h>
#include <engine/collisionmesh.h>
#include <physics/collider.h>
#include <physics/body.h>
#include <physics/physicssystem.h>

#include <scripts/entites/prop_static.h>

body_t			body = 0;

void Start( level_t Level )
{
	collisionMesh_t	collisionMesh;
	mesh_t			mesh = ResourceSystem_LoadMesh( "tv", "models/tv.mdl" );
	collider_t		collider = ResourceSystem_LoadCollider( "tv_coll", "models/tv.phy" );
		
	if ( !mesh || !collider )	
		return;

	body = Body_Create();
	vec3f_t			inertia = { 0.f, 0.f, 0.f };
	vec3f_t			pos = { 0.f, 150.f, 0.f };

	Body_Initialize( body, collider, 50, inertia, B_FALSE );
	Body_SetPosition( body, pos );

	model_t			model = Model_Create();
	Model_SetMesh( model, mesh );
	Model_SetPosition( model, pos );

	ent_propStatic_t		ent_propStatic = PropStatic_Create();
	PropStatic_SetModel( ent_propStatic, model, body );

	PhysicsSystem_AddBody( body );
	Level_AddEntity( Level, ent_propStatic );
}

void Update()
{
	if ( !body ) return;

	if ( InputSystem_IsKeyDown( BC_KEY_PAD_4 ) )
	{
		vec3f_t			impulse = { -50, 0.f, 0.f };
		vec3f_t			cneter = { 0.5f, 0.f, 0.5f };
		Body_ApplyImpulse( body, impulse, cneter );
	}

	if ( InputSystem_IsKeyDown( BC_KEY_PAD_6 ) )
	{
		vec3f_t			impulse = { 50, 0.f, 0.f };
		vec3f_t			cneter = { 0.5f, 0.f, 0.5f };
		Body_ApplyImpulse( body, impulse, cneter );
	}

	if ( InputSystem_IsKeyDown( BC_KEY_PAD_8 ) )
	{
		vec3f_t			impulse = { 0, 50.f, 0.f };
		vec3f_t			cneter = { 0.5f, 0.f, 0.5f };
		Body_ApplyImpulse( body, impulse, cneter );
	}

	if ( InputSystem_IsKeyDown( BC_KEY_PAD_2 ) )
	{
		vec3f_t			impulse = { 0, -50.f, 0.f };
		vec3f_t			cneter = { 0.5f, 0.f, 0.5f };
		Body_ApplyImpulse( body, impulse, cneter );
	}
}