//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "baseentity.h"

// ------------------------------------------------------------------------------------ //
// �������� ������
// ------------------------------------------------------------------------------------ //
void BaseEntity::Update( le::UInt32_t DeltaTime )
{}

// ------------------------------------------------------------------------------------ //
// ��������� ���������
// ------------------------------------------------------------------------------------ //
void BaseEntity::KeyValue( const char* Key, const char* Value )
{}

// ------------------------------------------------------------------------------------ //
// ������ �������
// ------------------------------------------------------------------------------------ //
void BaseEntity::SetLevel( le::ILevel* Level )
{
	level = Level;
}

// ------------------------------------------------------------------------------------ //
// ������ �������
// ------------------------------------------------------------------------------------ //
void BaseEntity::SetPosition( const le::Vector3D_t& Position )
{
	position = Position;
}

// ------------------------------------------------------------------------------------ //
// �������� �������
// ------------------------------------------------------------------------------------ //
le::ILevel* BaseEntity::GetLevel() const
{
	return level;
}

// ------------------------------------------------------------------------------------ //
// �������� �������
// ------------------------------------------------------------------------------------ //
const le::Vector3D_t& BaseEntity::GetPosition() const
{
	return position;
}

// ------------------------------------------------------------------------------------ //
// �����������
// ------------------------------------------------------------------------------------ //
BaseEntity::BaseEntity()
{}

// ------------------------------------------------------------------------------------ //
// ����������
// ------------------------------------------------------------------------------------ //
BaseEntity::~BaseEntity()
{}

// ------------------------------------------------------------------------------------ //
// ������������� ������ � bool
// ------------------------------------------------------------------------------------ //
bool BaseEntity::StringToBoolean( const std::string& Value )
{
	if ( Value == "True" || Value == "true" || Value == "1" )
		return true;

	return false;
}
#include "global.h"
#include "engine/iconsolesystem.h"
// ------------------------------------------------------------------------------------ //
// ������������� ������ � Vector3D
// ------------------------------------------------------------------------------------ //
le::Vector3D_t BaseEntity::StringToVector3D( const std::string& Value )
{
	if ( !Value.empty() )
	{
		std::stringstream		stringStream( Value );
		std::string				tempString;
		le::Vector3D_t			vector3D;
		float					temp;
		int						indexValue = 0;

		while ( !stringStream.eof() && indexValue < 3 )
		{
			stringStream >> tempString;

			switch (indexValue)
			{
			case 0:
				vector3D.x = std::atof(tempString.c_str());
				break;

			case 1:
				vector3D.y = std::atof(tempString.c_str());
				break;

			case 2:
				vector3D.z = std::atof(tempString.c_str());
				break;
			default:
				break;
			}

			// StringToNumber<float>( tempString );
			tempString.clear();
			indexValue++;
		}

		// ������ �������� Y � Z, � �������� ����� Z, ����� Y ��� �����. 
		temp = vector3D.y;
		vector3D.y = vector3D.z;
		vector3D.z = -temp;

		return vector3D;
	}

	return le::Vector3D_t();
}

// ------------------------------------------------------------------------------------ //
// ������������� ������ � Vector4D
// ------------------------------------------------------------------------------------ //
le::Vector4D_t BaseEntity::StringToVector4D( const std::string& Value )
{
	if ( !Value.empty() )
	{
		std::stringstream		stringStream( Value );
		std::string				tempString;
		le::Vector4D_t			vector4D;
		float					temp;
		int						indexValue = 0;

		while ( !stringStream.eof() && indexValue < 4 )
		{
			stringStream >> tempString;
			vector4D[ indexValue ] = StringToNumber<float>( tempString );
			tempString.clear();
			indexValue++;
		}

		// ������ �������� Y � Z, � �������� ����� Z, ����� Y ��� �����. 
		temp = vector4D.y;
		vector4D.y = vector4D.z;
		vector4D.z = -temp;

		return vector4D;
	}

	return le::Vector4D_t();
}
