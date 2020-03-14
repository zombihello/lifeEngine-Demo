//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <vector>
#include <time.h>

#include "engine/lifeengine.h"
#include "engine/iengine.h"
#include "engine/iconsolesystem.h"
#include "engine/iresourcesystem.h"
#include "engine/iwindow.h"
#include "engine/icamera.h"
#include "engine/iinputsystem.h"
#include "engine/iconcmd.h"
#include "studiorender/istudiorender.h"
#include "studiorender/itexture.h"
/*#include "studiorender/ipointlight.h"
#include "studiorender/ispotlight.h"
#include "studiorender/idirectionallight.h"*/
#include "player.h"
#include "engine/ifactory.h"
#include "engine/ilevel.h"
#include "engine/imodel.h"
#include "physics/iphysicssystem.h"
#include "physics/ibody.h" 
#include "global.h"
#include "game.h"
#include "func_rotating.h"
#include "func_door.h"
#include "info_player_start.h"

LIFEENGINE_GAME_API( Game );

le::IStudioRender*		g_studioRender = nullptr;
le::IMesh*				g_mesh = nullptr;
le::IEngine*			g_engine = nullptr;
le::ILevel*				g_level = nullptr;
/*le::ISpotLight*			g_spotLight = nullptr;
le::ISpotLight*			g_flashlight = nullptr;
le::IDirectionalLight*	g_directionalLight = nullptr;*/
le::IModel*				g_model = nullptr;
le::UInt32_t dt = 0;
le::UInt32_t width, height;
/*std::vector< le::IPointLight* >		pointlights;
std::vector< le::ISpotLight* >		spotlights;*/

bool a = false;
float player_speed = 1.f;
float angle = 0.f;


class GameFactory : public le::IFactory
{
public:
	// IFactory

	virtual void*			Create( const char* NameInterface )
	{
		if ( strcmp( NameInterface, "func_rotating" ) == 0 )				return new Func_Rotating();
		else if ( strcmp( NameInterface, "func_door" ) == 0 )				return new Func_Door();
		else if ( strcmp( NameInterface, "info_start_position" ) == 0 )		return new Info_Player_Start();

		return nullptr;
	}

	virtual void			Delete( void* Object )
	{
		if ( !Object ) return;
		delete Object;
	}
} g_gameFactory;

/*void CMD_CreateLight( le::UInt32_t CountArguments, const char** Arguments )
{
	if ( a || !g_studioRender || !g_camera || !g_level ) return;

	le::IPointLight*		light = ( le::IPointLight* ) g_studioRender->GetFactory()->Create( POINTLIGHT_INTERFACE_VERSION );
	if ( !light ) return;
a = true;
	light->SetPosition( g_camera->GetPosition() );
	light->SetIntensivity( 2500.f );
	light->SetColor( le::Vector4D_t( ( rand() % 255 ) / 255.f, ( rand() % 255 ) / 255.f, ( rand() % 255 ) / 255.f, 1.f ) );
	light->SetRadius( 500.f );
	g_level->AddPointLight( light );

	pointlights.push_back( light );
}*/

/*void CMD_CreateSpotLight( le::UInt32_t CountArguments, const char** Arguments )
{
	if ( a || !g_studioRender || !g_camera || !g_level ) return;

	le::ISpotLight*		light = ( le::ISpotLight* ) g_studioRender->GetFactory()->Create( SPOTLIGHT_INTERFACE_VERSION );
	if ( !light ) return;
a = true;
	light->SetPosition( g_camera->GetPosition() );
	light->SetIntensivity( 10000.f );
	light->SetRadius( 500.f );
	light->SetColor( le::Vector4D_t( ( rand() % 255 ) / 255.f, ( rand() % 255 ) / 255.f, ( rand() % 255 ) / 255.f, 1.f ) );
	light->SetHeight( 1000.f );
	g_level->AddSpotLight( light );

	spotlights.push_back( light );
}*/

/*void CMD_EnableDirectionalLight( le::UInt32_t CountArguments, const char** Arguments )
{
	if ( !g_level->GetDirectionalLight( 0 ) )
		g_level->AddDirectionalLight( g_directionalLight );
}

void CMD_DisableDirectionalLight( le::UInt32_t CountArguments, const char** Arguments )
{
	if ( g_level->GetDirectionalLight( 0 ) )
		g_level->RemoveDirectionalLight( g_directionalLight );
}
*/

// ------------------------------------------------------------------------------------ //
// Move player forward
// ------------------------------------------------------------------------------------ //
void CMD_MoveForward( le::UInt32_t CountArguments, const char** Arguments )
{
	player->Move(le::Vector3D_t(0, 0, -1) * player_speed );
	a=false;
}

// ------------------------------------------------------------------------------------ //
// Move player backward
// ------------------------------------------------------------------------------------ //
void CMD_MoveBackward( le::UInt32_t CountArguments, const char** Arguments )
{
	player->Move(le::Vector3D_t(0, 0, 1) * player_speed );
}

// ------------------------------------------------------------------------------------ //
// Move player left
// ------------------------------------------------------------------------------------ //
void CMD_MoveLeft( le::UInt32_t CountArguments, const char** Arguments )
{
	player->Move(le::Vector3D_t(-1, 0, 0) * player_speed );
}

// ------------------------------------------------------------------------------------ //
// Move player right
// ------------------------------------------------------------------------------------ //
void CMD_MoveRight( le::UInt32_t CountArguments, const char** Arguments )
{
	player->Move(le::Vector3D_t(1, 0, 0) * player_speed );
}

// ------------------------------------------------------------------------------------ //
// Player sprint
// ------------------------------------------------------------------------------------ //
void CMD_Sprint( le::UInt32_t CountArguments, const char** Arguments )
{
	player_speed = 2.f;
}

le::IPhysicsSystem* physics;

struct Entity
{
	le::IBody*		body;
	le::IModel*		model;
};

std::vector< Entity >		entites;

void CMD_CreateStyl( le::UInt32_t CountArguments, const char** Arguments )
{
	if (a) return;
	Entity		entity;
	entity.model = (le::IModel*) g_engine->GetFactory()->Create(MODEL_INTERFACE_VERSION);
	entity.body = (le::IBody*)physics->GetFactory()->Create(BODY_INTERFACE_VERSION);

	le::ShapeBoxDescriptor box;
	box.rigidity = 3;
	box.side = 35;

	entity.model->SetMesh( g_mesh );
	entity.model->SetPosition( player->GetPosition() );

	entity.body->Initialize(box, 35, le::Vector3D_t(0, 0, 0), le::BODY_TYPE::BT_DYNAMIC);
	entity.body->SetPosition(entity.model->GetPosition());

	physics->AddBody(entity.body);
	a = true;
	g_level->AddModel(entity.model);
	entites.push_back(entity);
}

// ------------------------------------------------------------------------------------ //
// Game Initialize
// TODO: Delete trash and add for body camera
// ------------------------------------------------------------------------------------ //
bool Game::Initialize( le::IEngine* Engine )
{	
	
	le::ShapeBoxDescriptor box;
	box.rigidity = 3;
	box.side = 35;
	physics = Engine->GetPhysicsSystem();

	le::IFactory*			factory = Engine->GetFactory();
	player = new Player();
	
	g_engine = Engine;
	g_consoleSystem = Engine->GetConsoleSystem();
	g_inputSystem = Engine->GetInputSystem();
	g_studioRender = Engine->GetStudioRender();
	g_physicsSystem = Engine->GetPhysicsSystem();
	g_consoleSystem->PrintInfo("It`s a Game Initialize");
	player->Initialize(g_engine);
	le::IConCmd*	cmd_move_forward = ( le::IConCmd* ) g_consoleSystem->GetFactory()->Create( CONCMD_INTERFACE_VERSION );
	le::IConCmd*	cmd_move_backward = ( le::IConCmd* ) g_consoleSystem->GetFactory()->Create( CONCMD_INTERFACE_VERSION );
	le::IConCmd*	cmd_move_left = ( le::IConCmd* ) g_consoleSystem->GetFactory()->Create( CONCMD_INTERFACE_VERSION );
	le::IConCmd*	cmd_move_right = ( le::IConCmd* ) g_consoleSystem->GetFactory()->Create( CONCMD_INTERFACE_VERSION );
	le::IConCmd*	cmd_sprint = ( le::IConCmd* ) g_consoleSystem->GetFactory()->Create( CONCMD_INTERFACE_VERSION );
	le::IConCmd*	cmd_createStyl = (le::IConCmd*) g_consoleSystem->GetFactory()->Create(CONCMD_INTERFACE_VERSION);

	cmd_move_forward->Initialize( "+move_forward", CMD_MoveForward );
	cmd_move_backward->Initialize( "+move_backward",CMD_MoveBackward );
	cmd_move_left->Initialize( "+move_left",CMD_MoveLeft );
	cmd_move_right->Initialize( "+move_right", CMD_MoveRight );
	cmd_sprint->Initialize( "+sprint",  CMD_Sprint );
	cmd_createStyl->Initialize("+createStyl", CMD_CreateStyl);

	g_consoleSystem->RegisterCommand( cmd_move_forward );
	g_consoleSystem->RegisterCommand( cmd_move_backward );
	g_consoleSystem->RegisterCommand( cmd_move_left );
	g_consoleSystem->RegisterCommand( cmd_move_right );
	g_consoleSystem->RegisterCommand( cmd_sprint );
	g_consoleSystem->RegisterCommand(cmd_createStyl);

	g_consoleSystem->Exec( "bind shift +sprint" );
	g_consoleSystem->Exec( "bind w +move_forward" );
	g_consoleSystem->Exec( "bind s +move_backward" );
	g_consoleSystem->Exec( "bind a +move_left" );
	g_consoleSystem->Exec( "bind d +move_right" );	
	g_consoleSystem->Exec( "bind q \"r_showgbuffer 1\"" );
	g_consoleSystem->Exec( "bind e \"r_showgbuffer 0\"" );
	g_consoleSystem->Exec( "bind esc exit" );
	g_consoleSystem->Exec("bind mouse1 +createStyl");
	g_consoleSystem->Exec( "help" );

	
	Engine->GetWindow()->SetShowCursor( false );

	g_mesh = Engine->GetResourceSystem()->LoadMesh( "box", "box.lmd" );
	if ( !g_mesh ) return false;

	g_model = ( le::IModel* ) factory->Create( MODEL_INTERFACE_VERSION );
	if ( !g_model ) return false;

	g_model->SetMesh( g_mesh );
	g_model->SetPosition( le::Vector3D_t( 0, 150, -55 ) );
	//body->SetGravity(le::Vector3D_t(0, -10, 0));

	Entity		entity;
	entity.model = g_model;
	entity.body = (le::IBody*)physics->GetFactory()->Create(BODY_INTERFACE_VERSION);
	entity.body->Initialize(box, 1, le::Vector3D_t(0, 0, 0), le::BODY_TYPE::BT_DYNAMIC);
	physics->AddBody(entity.body);
	entity.body->SetPosition(g_model->GetPosition());

	g_level = Engine->GetResourceSystem()->LoadLevel( "c0a0", "testbed_c0a0.bsp", ( le::IFactory* ) &g_gameFactory );
	if ( !g_level ) return false;

	player->GetCamera()->SetPosition( player->GetPosition() );
	g_level->AddCamera( player->GetCamera() );
	g_level->AddModel( g_model );

	
	
	return true;
}

// ------------------------------------------------------------------------------------ //
// Update game
// ------------------------------------------------------------------------------------ //
void Game::Update( le::UInt32_t DeltaTime )
{
	angle += 0.0008f * DeltaTime;
	player_speed = 0.08f;
	dt = DeltaTime;
	physics->Update(DeltaTime);
	player->Update();

	for (le::UInt32_t index = 0, count = entites.size(); index < count; ++index)
	{
		Entity*			entity = &entites[ index ];
		entity->model->SetPosition( entity->body->GetPosition() );
		entity->model->SetRotation( entity->body->GetRotation() );
	}

	g_level->Update( DeltaTime );

	if ( angle >= 360 )
		angle = 0.f;
}

// ------------------------------------------------------------------------------------ //
// Event in Game
// ------------------------------------------------------------------------------------ //
void Game::OnEvent( const le::Event& Event )
{}
