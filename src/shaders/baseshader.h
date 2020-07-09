//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef BASE_SHADER_H
#define BASE_SHADER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "common/shaderparaminfo.h"
#include "engine/ishader.h"
#include  "studiorender/igpuprogram.h"

//---------------------------------------------------------------------//

class BaseShader : public le::IShader
{
public:
	// IShader
	virtual void				OnDrawText( const le::Matrix4x4_t& Transformation, le::ICamera* Camera, le::ITexture* Glyph = nullptr );
	virtual void				OnDrawSprite( const le::Matrix4x4_t& Transformation, le::ICamera* Camera );
	virtual void				OnDrawStaticModel( const le::Matrix4x4_t& Transformation, le::ICamera* Camera, le::ITexture* Lightmap = nullptr );

	// BaseShader
	BaseShader();
	virtual ~BaseShader();

protected:
	bool								LoadShader( const std::string& Name, const std::string& Path, const std::vector< const char* >& Defines, le::UInt32_t Flags = 0 );

	le::IGPUProgram*					gpuProgram;

private:
	std::string				nameShader;
	le::UInt32_t			flagShader;
};

//---------------------------------------------------------------------//

#endif // !BASE_SHADER_H

