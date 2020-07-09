//////////////////////////////////////////////////////////////////////////
//
//          *** lifeEngine (Двигатель жизни) ***
//		Copyright (C) 2018-2020
//
// Репозиторий движка:      https://github.com/zombihello/lifeEngine
// Авторы:                  Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#version 330 core

layout( location = 0 ) in vec3      vertex_position;
layout( location = 1 ) in vec2      vertex_texCoords;

out vec2 		texCoords;
out vec2 		texCoords2;

uniform vec4        textureRect;
uniform mat4    	matrix_Projection;
uniform mat4		matrix_Transformation;

void main()
{
    texCoords = vertex_texCoords;
	texCoords2 = textureRect.xy + ( vertex_texCoords * textureRect.zw );
	
    gl_Position = matrix_Projection * matrix_Transformation * vec4( vertex_position, 1.f );
}
