//////////////////////////////////////////////////////////////////////////
//
//				*** Eliot: Episodic ***
//				Copyright (C) 2019
//
// ����������� ����:	https://github.com/zombihello/Eleot-Episodic
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////
#ifndef GLOBAL_H
#define GLOBAL_H

#include "engine/iconsolesystem.h"
#include "engine/iinputsystem.h"
#include "engine/icamera.h"
#include "physics/iphysicssystem.h"

class Player;

//---------------------------------------------------------------------//

extern le::IConsoleSystem*			g_consoleSystem;
extern le::IInputSystem*			g_inputSystem;
extern le::ICamera*					g_camera;
extern le::IPhysicsSystem*			g_physicsSystem;
extern Player* player;

//---------------------------------------------------------------------//
#endif //!GLOBAL_H
