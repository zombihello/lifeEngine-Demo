#include <engine/model.h>
#include <engine/resourcesystem.h>
#include <engine/level.h>
#include <engine/consolesystem.h>
#include <physics/collider.h>
#include <physics/physicsmodel.h>
#include <physics/physicssystem.h>
#include <engine/inputsystem.h>

#include <scripts/entites/prop_static.h>

body_t			body = 0;
model_t			model = 0;

void Start( level_t Level )
{
	mesh_t			mesh = ResourceSystem_LoadMesh( "tv", "models/hotel.mdl" );
	//physicsModel_t	physicsModel = ResourceSystem_LoadPhysicsModel( "tv", "models/window01.phy" );
	if ( !mesh /*|| !physicsModel*/ )	return;
	
	vec3f_t			pos = { 0.f, 250.f, 0.f };
	vec3f_t			scale = { 1.0f, 1.0f, 1.0f };
	vec3f_t			rot = { 0.f, 3.14f, 0.f };
	
	float			m[ 16 ] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	mat4_t			matrix;
	for ( int i = 0; i < 16; i++ )
		matrix.matrix[ i ] = m[ i ];

	//collider_t	collider = Collider_Create();
	//Collider_AddPhysicsModel( collider, physicsModel, matrix );
	//Collider_SetScale( collider, scale );

	//body = Body_Create();
	//Body_Initialize( body, collider, PhysicsModel_GetMasa( physicsModel ), PhysicsModel_GetInertia( physicsModel ), PhysicsModel_IsStatic( physicsModel ) );
	//ConsoleSystem_Info( "massa: %f , is static: %i", PhysicsModel_GetMasa( physicsModel ), PhysicsModel_IsStatic( physicsModel ) );
	//Body_SetPosition( body, pos );
	//PhysicsSystem_AddBody( body );
	
	model = Model_Create();
	Model_SetMesh( model, mesh );
	//Model_SetEulerRotation( model, rot );
	Model_SetPosition( model, pos );
	//Model_SetScale( model, scale );

	ent_propStatic_t		ent_propStatic = PropStatic_Create();
	PropStatic_SetModel( ent_propStatic, model, 0 );
	Level_AddEntity( Level, ent_propStatic );
}

void Update()
{
	if ( InputSystem_IsKeyDown( BC_KEY_DOWN ) )
	{
		vec3f_t		offset = { 0.f, -1.f, 0.f };
		//Model_Move( model, offset );
		//Body_SetPosition( body, Model_GetPosition( model ) );
	}
	
	if ( InputSystem_IsKeyDown( BC_KEY_UP ) )
	{
		vec3f_t		offset = { 0.f, 1.f, 0.f };
		vec3f_t		center = { 0.f, 0.f, 0.f };
	//	Body_ApplyImpulse( body, offset, center );
		//Model_Move( model, offset );
		//Body_SetPosition( body, Model_GetPosition( model ) );
	}
	
	if ( InputSystem_IsKeyDown( BC_KEY_LEFT ) )
	{
		vec3f_t		offset = { 0.f, 0.f, -1.f };
		//Model_Move( model, offset );
		//Body_SetPosition( body, Model_GetPosition( model ) );
	}
	
	if ( InputSystem_IsKeyDown( BC_KEY_RIGHT ) )
	{
		vec3f_t		offset = { 0.f, 0.f, 1.f };
		//Model_Move( model, offset );
		//Body_SetPosition( body, Model_GetPosition( model ) );
	}
}