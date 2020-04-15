//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "engine/ifactory.h"
#include "physics/shapecapsuledescriptor.h"

#include "global.h"
#include "game.h"
#include "player.h"
#include "input.h"

#define			PLAYER_HEIGHT           161.f
#define			PLAYER_RADIUS           20.f
#define         CAMERA_MAX_TILT         3.f
#define         CAMERA_OFFSET_TILT      0.5f

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Player::Player() :
    camera( nullptr ),
    isInitialize( false ),
    controller( nullptr ),
    cameraType( CT_PHYSICS ),
    tiltCamera( 0.f )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Player::~Player()
{
    if ( !isInitialize ) return;

    g_physicsSystem->SetDebugCamera( nullptr );
    DeleteBody();

    if ( camera->GetCountReferences() <= 1 )	camera->Release();
    else										camera->DecrementReference();
}

// ------------------------------------------------------------------------------------ //
// Initialize player
// ------------------------------------------------------------------------------------ //
void Player::Initialize()
{
    if ( isInitialize )		return;

    // Initialize camera
    le::IFactory*			engineFactory = g_engine->GetFactory();
    camera = ( le::ICamera* ) engineFactory->Create( CAMERA_INTERFACE_VERSION );
    if ( !camera )			throw std::runtime_error( "le::ICamera interface version[" CAMERA_INTERFACE_VERSION "] not found in engine factory" );

    le::UInt32_t		windowWidth, windowHeight;
    g_window->GetSize( windowWidth, windowHeight );

    camera->IncrementReference();
    camera->InitProjection_Perspective( 75.f, ( float ) windowWidth / ( float ) windowHeight, 0.1f, 2500.f );
    g_physicsSystem->SetDebugCamera( camera );

    // Initialize body
    CreateBody();

    isInitialize = true;
}

// ------------------------------------------------------------------------------------ //
// Update player
// ------------------------------------------------------------------------------------ //
void Player::Update()
{	
    camera->RotateByMouse( g_inputSystem->GetMouseOffset(), g_inputSystem->GetMouseSensitivity() );

    Input*			input = Input::GetInstance();
    bool			isSprint = input->IsButtonDown( BT_SPRINT );

    switch ( cameraType )
    {
    case CT_PHYSICS:
    {
        le::Vector3D_t				offsetDirection( 0.f, 0.f, 0.f );
        le::Vector3D_t				position = controller->GetPosition();
        position.y += PLAYER_HEIGHT / 2.f;

        if ( input->IsButtonDown( BT_MOVE_FORWARD ) )		offsetDirection += camera->GetDirectionMove( le::CSM_FORWARD );
        if ( input->IsButtonDown( BT_MOVE_BACKWARD ) )		offsetDirection += camera->GetDirectionMove( le::CSM_BACKWARD );
        if ( input->IsButtonDown( BT_MOVE_LEFT ) )
        {
            offsetDirection += camera->GetDirectionMove( le::CSM_LEFT );
            if ( tiltCamera > -CAMERA_MAX_TILT )
            {
                tiltCamera -= CAMERA_OFFSET_TILT;
                camera->Rotate( le::Vector3D_t( 0.f, 0.f, -CAMERA_OFFSET_TILT ) );
            }
        }
        if ( input->IsButtonDown( BT_MOVE_RIGHT ) )
        {
            offsetDirection += camera->GetDirectionMove( le::CSM_RIGHT );
            if ( tiltCamera < CAMERA_MAX_TILT )
            {
                tiltCamera += CAMERA_OFFSET_TILT;
                camera->Rotate( le::Vector3D_t( 0.f, 0.f, CAMERA_OFFSET_TILT ) );
            }
        }
        if ( input->IsButtonDown( BT_JUMP ) && controller->OnGround()  )
            controller->Jump( le::Vector3D_t( 0.f, 80.f, 0.f ) );

        if ( !input->IsButtonDown( BT_MOVE_LEFT ) && !input->IsButtonDown( BT_MOVE_RIGHT ) )
        {
            if ( tiltCamera + CAMERA_OFFSET_TILT < 0 )
            {
                camera->Rotate( le::Vector3D_t( 0.f, 0.f, CAMERA_OFFSET_TILT ) );
                tiltCamera += CAMERA_OFFSET_TILT;
            }
            else if ( tiltCamera - CAMERA_OFFSET_TILT > 0 )
            {
                camera->Rotate( le::Vector3D_t( 0.f, 0.f, -CAMERA_OFFSET_TILT ) );
                tiltCamera -= CAMERA_OFFSET_TILT;
            }
        }

        if ( offsetDirection.x != 0 || offsetDirection.z != 0 )
        {
            offsetDirection.y = 0.f;
            controller->Walk( offsetDirection * ( 2.f + 3.f * ( int ) isSprint ) );
        }
        else if ( controller->OnGround() )
            controller->Walk( le::Vector3D_t( 0, 0, 0 ) );

        camera->SetPosition( position );
        break;
    }

    case CT_FLY:
        if ( Input::GetInstance()->IsButtonDown( BT_MOVE_FORWARD ) )			camera->Move( le::CSM_FORWARD, 8.f + 10.f * ( int ) isSprint );
        if ( Input::GetInstance()->IsButtonDown( BT_MOVE_BACKWARD ) )			camera->Move( le::CSM_BACKWARD, 8.f + 10.f * ( int ) isSprint );
        if ( Input::GetInstance()->IsButtonDown( BT_MOVE_LEFT ) )				camera->Move( le::CSM_LEFT, 8.f + 10.f * ( int ) isSprint );
        if ( Input::GetInstance()->IsButtonDown( BT_MOVE_RIGHT ) )				camera->Move( le::CSM_RIGHT, 8.f + 10.f * ( int ) isSprint );
        break;
    }
}

// ------------------------------------------------------------------------------------ //
// Set camera type
// ------------------------------------------------------------------------------------ //
void Player::SetCameraType( CAMERA_TYPE CameraType )
{
    switch ( CameraType )
    {
    case CT_PHYSICS:
        if ( !controller ) CreateBody();
        break;

    case CT_FLY:
        if ( controller ) DeleteBody();
        break;
    }

    cameraType = CameraType;
}

// ------------------------------------------------------------------------------------ //
// Set position
// ------------------------------------------------------------------------------------ //
void Player::SetPosition( const le::Vector3D_t& Position )
{
    if ( !isInitialize ) return;

    switch ( cameraType )
    {
    case CT_PHYSICS:
        controller->SetPosition( Position );
        break;

    case CT_FLY:
        camera->SetPosition( Position );
        break;
    }
}

// ------------------------------------------------------------------------------------ //
// Create body
// ------------------------------------------------------------------------------------ //
void Player::CreateBody()
{
    if ( controller ) return;

    le::IFactory*			physicsFactory = g_physicsSystem->GetFactory();
    controller = ( le::ICharcterController* ) physicsFactory->Create( CHARCTERCONTROLLER_INTERFACE_VERSION );
    if ( !controller )			throw std::runtime_error( "le::ICharcterController interface version[" CHARCTERCONTROLLER_INTERFACE_VERSION "] not found in physics factory" );

    le::ShapeCapsuleDescriptor			shapeCapsuleDescriptor;
    shapeCapsuleDescriptor.height = PLAYER_HEIGHT;
    shapeCapsuleDescriptor.radius = PLAYER_RADIUS;

    controller->IncrementReference();
    controller->Initialize( shapeCapsuleDescriptor );

    le::Vector3D_t			position = camera->GetPosition();
    position.y -= PLAYER_HEIGHT / 2.f;
    controller->SetPosition( position );
    g_physicsSystem->AddCharcterController( controller );
}

// ------------------------------------------------------------------------------------ //
// Delete body
// ------------------------------------------------------------------------------------ //
void Player::DeleteBody()
{
    if ( !controller ) return;

    g_physicsSystem->RemoveCharcterController( controller );
    if ( controller->GetCountReferences() <= 1 )		controller->Release();
    else												controller->DecrementReference();

    controller = nullptr;
}
