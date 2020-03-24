//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "baseentity.h"

// ------------------------------------------------------------------------------------ //
// Update logic
// ------------------------------------------------------------------------------------ //
void BaseEntity::Update()
{}

// ------------------------------------------------------------------------------------ //
// Set values
// ------------------------------------------------------------------------------------ //
void BaseEntity::KeyValue( const char* Key, const char* Value )
{}

// ------------------------------------------------------------------------------------ //
// Set level
// ------------------------------------------------------------------------------------ //
void BaseEntity::SetLevel( le::ILevel* Level )
{
	level = Level;
}

// ------------------------------------------------------------------------------------ //
// Set position
// ------------------------------------------------------------------------------------ //
void BaseEntity::SetPosition( const le::Vector3D_t& Position )
{
	position = Position;
}

// ------------------------------------------------------------------------------------ //
// Get level
// ------------------------------------------------------------------------------------ //
le::ILevel* BaseEntity::GetLevel() const
{
	return level;
}

// ------------------------------------------------------------------------------------ //
// Get position
// ------------------------------------------------------------------------------------ //
const le::Vector3D_t& BaseEntity::GetPosition() const
{
	return position;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
BaseEntity::BaseEntity()
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
BaseEntity::~BaseEntity()
{}

// ------------------------------------------------------------------------------------ //
// String to bool
// ------------------------------------------------------------------------------------ //
bool BaseEntity::StringToBoolean( const std::string& Value )
{
	if ( Value == "True" || Value == "true" || Value == "1" )
		return true;

	return false;
}

// ------------------------------------------------------------------------------------ //
// String to vector3
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
			vector3D[ indexValue ] = StringToNumber<float>( tempString );
			tempString.clear();
			indexValue++;
		}

		// Flip z and y
		temp = vector3D.y;
		vector3D.y = vector3D.z;
		vector3D.z = -temp;

		return vector3D;
	}

	return le::Vector3D_t();
}

// ------------------------------------------------------------------------------------ //
// String to vector4
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

		// Flip z and y
		temp = vector4D.y;
		vector4D.y = vector4D.z;
		vector4D.z = -temp;

		return vector4D;
	}

	return le::Vector4D_t();
}
