//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef PROP_STATIC_H
#define PROP_STATIC_H

#include "engine/iscript.h"
#include "baseentity.h"

//---------------------------------------------------------------------//

class Prop_Static : public BaseEntity
{
public:
	// IEntity
	virtual void				KeyValue( const char* Key, const char* Value );
	virtual void				Update();
	virtual void				Render( le::IStudioRender* StudioRender );

	virtual void				SetModel( le::IModel* Model, le::IBody* Body );

	virtual bool				IsVisible( le::ICamera* Camera ) const;
	virtual le::Vector3D_t		GetCenter() const;

	// Prop_Static
	Prop_Static();
	~Prop_Static();

private:
	le::IModel*			model;
	le::IBody*			body;
};

//---------------------------------------------------------------------//

#endif // !PROP_STATIC_H
