//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef FUNC_DOOR_H
#define FUNC_DOOR_H

#include "engine/imodel.h"
#include "physics/ibody.h"
#include "baseentity.h"

//---------------------------------------------------------------------//

class Func_Door : public BaseEntity
{
public:
	// IEntity
	virtual void					KeyValue( const char* Key, const char* Value );
	virtual void					Update();
	virtual void					Render( le::IStudioRender* StudioRender );

	virtual void					SetModel( le::IModel* Model, le::IBody* Body );

	virtual bool					IsVisible( le::ICamera* Camera ) const;
	virtual le::Vector3D_t			GetCenter() const;

	// Func_Door
	Func_Door();
	~Func_Door();

private:
	bool					isOpen;
	bool					isClose;

	float					donePercentag;
	float					angleMax;
	float					speedOpen;
	float					speedClose;

	le::IModel*				model;
	le::IBody*				body;
	le::Quaternion_t		startRotation;
	le::Quaternion_t		endRotation;	
};

//---------------------------------------------------------------------//

#endif // !FUNC_DOOR_H
