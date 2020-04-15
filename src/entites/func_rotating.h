//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef FUNC_ROTATING_H
#define FUNC_ROTATING_H

#include "common/types.h"
#include "engine/imodel.h"
#include "physics/ibody.h"

#include "baseentity.h"

//---------------------------------------------------------------------//

class Func_Rotating : public BaseEntity
{
public:
	// IEntity	
	virtual void					KeyValue( const char* Key, const char* Value );
	virtual void					Update();
	virtual void					Render( le::IStudioRender* StudioRender );

	virtual void					SetModel( le::IModel* Model, le::IBody* Body );
	virtual bool					IsVisible( le::ICamera* Camera ) const;
	virtual le::Vector3D_t			GetCenter() const;

	// Func_Rotating
	Func_Rotating();
	~Func_Rotating();

private:
	float					speed;	

	le::IModel*				model;
	le::IBody*				body;
};

//---------------------------------------------------------------------//

#endif // !FUNC_ROTATING_H

