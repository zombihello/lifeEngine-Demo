//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef PROP_POINTLIGHT_H
#define PROP_POINTLIGHT_H

#include "studiorender/ipointlight.h"
#include "baseentity.h"

//---------------------------------------------------------------------//

class Prop_PointLight : public BaseEntity
{
public:
	// IEntity
	virtual void				KeyValue( const char* Key, const char* Value );
	virtual void				Update();
	virtual void				Render( le::IStudioRender* StudioRender );

	virtual void				SetModel( le::IModel* Model, le::IBody* Body );
	virtual void				SetPosition( const le::Vector3D_t& Position );

	virtual bool				IsVisible( le::ICamera* Camera ) const;
	virtual le::Vector3D_t		GetCenter() const;

	// Prop_PointLight
	Prop_PointLight();
	~Prop_PointLight();

private:
	le::IPointLight*			pointLight;
};

//---------------------------------------------------------------------//

#endif // !PROP_POINTLIGHT_H
