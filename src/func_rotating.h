//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef FUNC_ROTATING_H
#define FUNC_ROTATING_H

#include "engine/imodel.h"
#include "baseentity.h"

//---------------------------------------------------------------------//

class Func_Rotating : public BaseEntity
{
public:
	// IEntity
	virtual void					Update( le::UInt32_t DeltaTime );
	virtual void					KeyValue( const char* Key, const char* Value );

	// Func_Rotating
	Func_Rotating();

private:
	bool					isNeedUpdatePosition;
	float					speed;
	le::IModel*				model;
};

//---------------------------------------------------------------------//

#endif // !FUNC_ROTATING_H

