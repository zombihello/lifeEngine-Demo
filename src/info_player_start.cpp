//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "global.h"
#include "player.h"
#include "info_player_start.h"
#include "engine/iconsolesystem.h"
// ------------------------------------------------------------------------------------ //
// �������� ������
// ------------------------------------------------------------------------------------ //
void Info_Player_Start::Update( le::UInt32_t DeltaTime )
{}

// ------------------------------------------------------------------------------------ //
// ��������� ���������
// ------------------------------------------------------------------------------------ //
void Info_Player_Start::KeyValue( const char* Key, const char* Value )
{
	if ( strcmp( Key, "origin" ) == 0 )
	{
		position = StringToVector3D( Value );
		position.y += 50;
		player->SetPosition( position );
	}
}
