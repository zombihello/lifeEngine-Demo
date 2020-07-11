//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef PROP_SPOTLIGHT_H
#define PROP_SPOTLIGHT_H

#include "studiorender/ispotlight.h"
#include "baseentity.h"

//---------------------------------------------------------------------//

class Prop_SpotLight : public BaseEntity
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

	// Prop_SpotLight
	Prop_SpotLight();
	~Prop_SpotLight();

	void						SetRotation( const le::Quaternion_t& Quaternion );
	void						SetRadius( float Radius );
	void						SetHeight( float Height );
	void						SetColor( const le::Vector4D_t& Color );
	void						SetSpecular( const le::Vector4D_t& Color );
	void						SetIntensivity( float Intensivity );

	const le::Vector4D_t		GetColor() const;
	const le::Vector4D_t		GetSpecular() const;
	float						GetIntensivity() const;
	const le::Quaternion_t		GetRotation() const;
	float						GetRadius() const;
	float						GetHeight() const;

private:
	le::ISpotLight*				spotLight;
};

//---------------------------------------------------------------------//

#endif // !PROP_SPOTLIGHT_H
