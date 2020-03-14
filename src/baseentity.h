//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include <sstream>

#include "engine/ientity.h"

//---------------------------------------------------------------------//

class BaseEntity : public le::IEntity
{
public:
	// IEntity
	virtual void					Update( le::UInt32_t DeltaTime );
	virtual void					KeyValue( const char* Key, const char* Value );

	virtual void					SetLevel( le::ILevel* Level );
	virtual void					SetPosition( const le::Vector3D_t& Position );

	virtual le::ILevel*				GetLevel() const;
	virtual const le::Vector3D_t&	GetPosition() const;

	// BaseEntity
	BaseEntity();
	virtual ~BaseEntity();

protected:
	bool						StringToBoolean( const std::string& Value );
	le::Vector3D_t				StringToVector3D( const std::string& Value );
	le::Vector4D_t				StringToVector4D( const std::string& Value );
	template< typename T >  T	StringToNumber( const std::string& Value, T DefValue = T() )
	{
		std::stringstream		stringStream;
		T						result;

		for ( auto it = Value.begin(), itEnd = Value.end(); it != itEnd; ++it )
			if ( isdigit( *it ) || *it == 'e' || *it == '-' || *it == '+' || *it == '.' )
				stringStream << *it;

		return stringStream >> result ? result : DefValue;
	}

	le::ILevel*					level;
	le::Vector3D_t				position;
};

//---------------------------------------------------------------------//

#endif // !BASE_ENTITY_H

