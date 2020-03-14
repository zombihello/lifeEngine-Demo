//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef FUNC_DOOR_H
#define FUNC_DOOR_H

#include "engine/imodel.h"
#include "baseentity.h"

//---------------------------------------------------------------------//

class Func_Door : public BaseEntity
{
public:
	// IEntity
	virtual void					Update( le::UInt32_t DeltaTime );
	virtual void					KeyValue( const char* Key, const char* Value );

	// Func_Door
	Func_Door();

private:
	bool					isNeedUpdate;
	bool					isOpen;
	bool					isClose;

	float					donePercentag;
	float					angleMax;
	float					speedOpen;
	float					speedClose;

	le::IModel*				model;
	le::Quaternion_t		startRotation;
	le::Quaternion_t		endRotation;
};

//---------------------------------------------------------------------//

#endif // !FUNC_DOOR_H

