//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/ifactory.h"
#include "engine/iresourcesystem.h"
#include "engine/iconsolesystem.h"

#include "global.h"
#include "baseshader.h"

// ------------------------------------------------------------------------------------ //
// Event: draw text
// ------------------------------------------------------------------------------------ //
void BaseShader::OnDrawText( const le::Matrix4x4_t& Transformation, le::ICamera* Camera, le::ITexture* Glyph )
{
	static bool			isPrintedWarning = false;
	if ( !isPrintedWarning )
	{
		g_consoleSystem->PrintWarning( "BaseShader::OnDrawText not implemented for shader [%s]", GetName() );
		isPrintedWarning = true;
	}
}

// ------------------------------------------------------------------------------------ //
// Event: draw sprite
// ------------------------------------------------------------------------------------ //
void BaseShader::OnDrawSprite( const le::Matrix4x4_t& Transformation, le::ICamera* Camera )
{
	static bool			isPrintedWarning = false;
	if ( !isPrintedWarning )
	{
		g_consoleSystem->PrintWarning( "BaseShader::OnDrawSprite not implemented for shader [%s]", GetName() );
		isPrintedWarning = true;
	}
}

// ------------------------------------------------------------------------------------ //
// Event: draw static model
// ------------------------------------------------------------------------------------ //
void BaseShader::OnDrawStaticModel( const le::Matrix4x4_t& Transformation, le::ICamera* Camera, le::ITexture* Lightmap )
{
	static bool			isPrintedWarning = false;
	if ( !isPrintedWarning )
	{
		g_consoleSystem->PrintWarning( "BaseShader::OnDrawStaticModel not implemented for shader [%s]", GetName() );
		isPrintedWarning = true;
	}
}

// ------------------------------------------------------------------------------------ //
// Конструктор
// ------------------------------------------------------------------------------------ //
BaseShader::BaseShader() :
	gpuProgram( nullptr ),
	flagShader( 0 )
{}

// ------------------------------------------------------------------------------------ //
// Деструктор
// ------------------------------------------------------------------------------------ //
BaseShader::~BaseShader()
{
	if ( gpuProgram )
	{
		gpuProgram->DecrementReference();
		g_resourceSystem->UnloadGPUProgram( nameShader.c_str(), flagShader );
	}
}

// ------------------------------------------------------------------------------------ //
// Загрузить шейдер
// ------------------------------------------------------------------------------------ //
bool BaseShader::LoadShader( const std::string& Name, const std::string& Path, const std::vector< const char* >& Defines, le::UInt32_t Flags )
{
	gpuProgram = g_resourceSystem->LoadGPUProgram( Name.c_str(), Path.c_str(), Flags, Defines.size(), ( const char** ) Defines.data() );
	
	if ( gpuProgram )
	{
		gpuProgram->IncrementReference();
		flagShader = Flags;
	}

	return gpuProgram;
}