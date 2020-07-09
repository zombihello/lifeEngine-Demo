//////////////////////////////////////////////////////////////////////////
//
//			        *** lifeEngine ***
//				Copyright (C) 2018-2020
//
// Repository engine:   https://github.com/zombihello/lifeEngine
// Authors:				Egor Pogulyaka (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "engine/icamera.h"
#include "engine/iconsolesystem.h"
#include "engine/ishaderparameter.h"
#include "studiorender/itexture.h"
#include "studiorender/igpuprogram.h"

#include "global.h"
#include "mytextshader.h"

// ------------------------------------------------------------------------------------ //
// Initialize parameters
// ------------------------------------------------------------------------------------ //
bool MyTextShader::Initialize( le::UInt32_t CountParams, le::IShaderParameter** ShaderParameters )
{
	std::vector< const char* >			defines;
	le::UInt32_t						flags = 0;

	if ( !LoadShader( "MyTextShader", "shaders/mytextshader.shader", defines, flags ) )
		return false;

	for ( le::UInt32_t index = 0; index < CountParams; ++index )
	{
		le::IShaderParameter*			shaderParameter = ShaderParameters[ index ];
		if ( !shaderParameter->IsDefined() )		continue;

		switch ( shaderParameter->GetType() )
		{
		case le::SPT_TEXTURE:
			if ( strcmp( shaderParameter->GetName(), "basetexture" ) == 0 )
			{
				basetexture = shaderParameter->GetValueTexture();
				basetexture->IncrementReference();
			}
			break;

		case le::SPT_VECTOR_4D:
			if ( strcmp( shaderParameter->GetName(), "textureRect" ) == 0 )
				textureRect = shaderParameter->GetValueVector4D();
			break;

		default:		continue;
		}
	}

	gpuProgram->Bind();
	gpuProgram->SetUniform( "basetexture", 0 );
	gpuProgram->SetUniform( "glyph", 1 );
	gpuProgram->Unbind();

	return true;
}

// ------------------------------------------------------------------------------------ //
// Event: draw text
// ------------------------------------------------------------------------------------ //
void MyTextShader::OnDrawText( const le::Matrix4x4_t& Transformation, le::ICamera* Camera, le::ITexture* Glyph )
{
	if ( !gpuProgram ) return;

	if ( basetexture )		basetexture->Bind( 0 );
	if ( Glyph )			Glyph->Bind( 1 );

	gpuProgram->Bind();
	gpuProgram->SetUniform( "textureRect", textureRect );
	gpuProgram->SetUniform( "matrix_Projection", Camera->GetProjectionMatrix() * Camera->GetViewMatrix() );
	gpuProgram->SetUniform( "matrix_Transformation", Transformation );
}

// ------------------------------------------------------------------------------------ //
// Get name
// ------------------------------------------------------------------------------------ //
const char* MyTextShader::GetName() const
{
	return "MyTextShader";
}

// ------------------------------------------------------------------------------------ //
// Get fallback shader
// ------------------------------------------------------------------------------------ //
const char* MyTextShader::GetFallbackShader() const
{
	return nullptr;
}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
MyTextShader::MyTextShader() :
	basetexture( nullptr )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
MyTextShader::~MyTextShader()
{
	ClearParameters();
}

// ------------------------------------------------------------------------------------ //
// Clear parameters
// ------------------------------------------------------------------------------------ //
void MyTextShader::ClearParameters()
{
	if ( basetexture )
	{
		if ( basetexture->GetCountReferences() <= 1 )		basetexture->Release();
		else basetexture->DecrementReference();

		basetexture = nullptr;
	}
}

// ------------------------------------------------------------------------------------ //
// Get descriptor
// ------------------------------------------------------------------------------------ //
le::ShaderDescriptor MyTextShader::GetDescriptor()
{
	static std::vector< le::ShaderParamInfo >			parametersInfo =
	{
		{ "basetexture", le::SPT_TEXTURE },
		{ "textureRect", le::SPT_VECTOR_4D }
	};

	le::ShaderDescriptor			shaderDescriptor;
	shaderDescriptor.name = "MyTextShader";
	shaderDescriptor.CreateShaderFn = []() -> IShader* { return new MyTextShader(); };
	shaderDescriptor.countParameters = parametersInfo.size();
	shaderDescriptor.parametersInfo = parametersInfo.data();
	return shaderDescriptor;
}

// ------------------------------------------------------------------------------------ //
// Is equal
// ------------------------------------------------------------------------------------ //
bool MyTextShader::IsEuqal( le::IShader* Shader ) const
{
	MyTextShader*			shader = ( MyTextShader* ) Shader;
	return strcmp( GetName(), Shader->GetName() ) == 0;
}