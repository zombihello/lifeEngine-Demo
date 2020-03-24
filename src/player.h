//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

#include "engine/iconcmd.h"
#include "engine/icamera.h"
#include "physics/icharactercontroller.h"

#include "tsingleton.h"

//---------------------------------------------------------------------//

enum CAMERA_TYPE
{
	CT_PHYSICS,
	CT_FLY
};

//---------------------------------------------------------------------//

class Player : public TSingleton< Player >
{
public:
	// Player
	Player();
	~Player();

	void					Initialize();
	void					Update();

	void					SetCameraType( CAMERA_TYPE CameraType );
	void					SetPosition( const le::Vector3D_t& Position );

	inline le::ICamera*		GetCamera() const	{ return camera; }

private:
	void					CreateBody();
	void					DeleteBody();

	bool							isInitialize;

	CAMERA_TYPE						cameraType;
	le::ICamera*					camera;
	le::ICharcterController*		controller;
};

//---------------------------------------------------------------------//

#endif // !PLAYER_H
