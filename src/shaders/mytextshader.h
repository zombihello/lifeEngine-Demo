//////////////////////////////////////////////////////////////////////////
//
//			        *** lifeEngine ***
//				Copyright (C) 2018-2020
//
// Repository engine:   https://github.com/zombihello/lifeEngine
// Authors:				Egor Pogulyaka (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef MYTEXTSHADER_H
#define MYTEXTSHADER_H

#include "engine/shaderdescriptor.h"
#include "baseshader.h"

//---------------------------------------------------------------------//

class MyTextShader : public BaseShader
{
public:
	// IShader
	virtual bool						Initialize( le::UInt32_t CountParams, le::IShaderParameter** ShaderParameters );
	virtual void						OnDrawText( const le::Matrix4x4_t& Transformation, le::ICamera* Camera, le::ITexture* Glyph = nullptr );

	virtual bool						IsEuqal( IShader* Shader ) const;
	virtual const char*					GetName() const;
	virtual const char*					GetFallbackShader() const;

	// MyTextShader
	MyTextShader();
	~MyTextShader();

	void								ClearParameters();
	static le::ShaderDescriptor			GetDescriptor();

private:
	le::ITexture*			basetexture;
	le::Vector4D_t			textureRect;
};

//---------------------------------------------------------------------//

#endif // !MYTEXTSHADER_H

