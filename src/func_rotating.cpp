//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/ilevel.h"
#include "func_rotating.h"

// ------------------------------------------------------------------------------------ //
// �������� ������
// ------------------------------------------------------------------------------------ //
void Func_Rotating::Update( le::UInt32_t DeltaTime )
{
	if ( !model ) return;

	if ( isNeedUpdatePosition )
	{
		model->SetPosition( position );
		isNeedUpdatePosition = false;
	}

	model->Rotate( le::Vector3D_t( 0, 2 * (speed * DeltaTime), 0 ) );
}

// ------------------------------------------------------------------------------------ //
// ��������� ���������
// ------------------------------------------------------------------------------------ //
void Func_Rotating::KeyValue( const char* Key, const char* Value )
{
	if ( level && strcmp( Key, "model" ) == 0 )
	{
		int			idModel = StringToNumber< int >( Value, -1 );
		if ( idModel == -1 )		return;

		model = level->GetModel( idModel );
	}
	else if ( strcmp( Key, "Speed" ) == 0 )
		speed = StringToNumber< float >( Value, 0.0008f );
	else if ( strcmp( Key, "origin" ) == 0 )
	{
		position = StringToVector3D( Value );
		isNeedUpdatePosition = true;
	}
}

// ------------------------------------------------------------------------------------ //
// �����������
// ------------------------------------------------------------------------------------ //
Func_Rotating::Func_Rotating() :
	isNeedUpdatePosition( false ),
	model( nullptr ),
	speed( 0.0008f )
{}
