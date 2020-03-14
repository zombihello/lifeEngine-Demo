//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "common/buttoncode.h"
#include "engine/ilevel.h"

#include "global.h"
#include "func_door.h"

// ------------------------------------------------------------------------------------ //
// �������� ������
// ------------------------------------------------------------------------------------ //
void Func_Door::Update( le::UInt32_t DeltaTime )
{
	if ( !model ) return;

	if ( isNeedUpdate )
	{
		model->SetPosition( position );
		startRotation = le::Quaternion_t( le::Vector3D_t( 0.f, 0.f, 0.f ) );
		endRotation = le::Quaternion_t( le::Vector3D_t( 0.f, glm::radians( angleMax ), 0.f ) );
		isNeedUpdate = false;
	}

	if ( g_inputSystem->IsKeyDown( le::BC_KEY_F ) )
	{
		isOpen = true; 
		isClose = false;
	}
	else if ( g_inputSystem->IsKeyUp( le::BC_KEY_F ) && isOpen )
	{
		isOpen = false;
		isClose = true;
	}

	if ( isOpen && donePercentag < 1.f )
	{
		donePercentag = glm::min( 1.f, donePercentag + ( speedOpen * DeltaTime ) );
		model->SetRotation( glm::slerp( startRotation, endRotation, donePercentag ) );
	}
	else if ( isClose && donePercentag > 0.f )
	{
		donePercentag = glm::max( 0.f, donePercentag - ( speedClose * DeltaTime ) );
		model->SetRotation( glm::slerp( startRotation, endRotation, donePercentag ) );
	}
}

// ------------------------------------------------------------------------------------ //
// ��������� ���������
// ------------------------------------------------------------------------------------ //
void Func_Door::KeyValue( const char* Key, const char* Value )
{
	if ( level && strcmp( Key, "model" ) == 0 )
	{
		int			idModel = StringToNumber< int >( Value, -1 );
		if ( idModel == -1 )		return;

		model = level->GetModel( idModel );
	}
	else if ( strcmp( Key, "origin" ) == 0 )
	{
		position = StringToVector3D( Value );
		isNeedUpdate = true;
	}
	else if ( strcmp( Key, "AngleMax" ) == 0 )
	{
		angleMax = StringToNumber< float >( Value, 90.f );
		isNeedUpdate = true;
	}
	else if ( strcmp( Key, "SpeedOpen" ) == 0 )
		speedOpen = StringToNumber< float >( Value, 0.0008f );
	else if ( strcmp( Key, "SpeedClose" ) == 0 )
		speedClose = StringToNumber< float >( Value, 0.0008f );
}

// ------------------------------------------------------------------------------------ //
// �����������
// ------------------------------------------------------------------------------------ //
Func_Door::Func_Door() :
	isNeedUpdate( false ),
	isOpen( false ),
	isClose( true ),
	model( nullptr ),
	donePercentag( 0.f ),
	angleMax( 90.f ),
	speedOpen( 0.0008f ),
	speedClose( 0.0008f )
{}
