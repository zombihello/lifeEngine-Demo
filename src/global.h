//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GLOBAL_H
#define GLOBAL_H

#include "engine/iengine.h"
#include "engine/iconsolesystem.h"
#include "engine/iinputsystem.h"
#include "engine/iresourcesystem.h"
#include "engine/iwindow.h"
#include "studiorender/istudiorender.h"
#include "physics/iphysicssystem.h"

#include "engine/icamera.h"

//---------------------------------------------------------------------//

class Game;

//---------------------------------------------------------------------//

extern le::IEngine*				g_engine;
extern le::IConsoleSystem*		g_consoleSystem;
extern le::IInputSystem*		g_inputSystem;
extern le::IStudioRender*		g_studioRender;
extern le::IResourceSystem*		g_resourceSystem;
extern le::IPhysicsSystem*		g_physicsSystem;
extern le::IWindow*				g_window;

//---------------------------------------------------------------------//

#endif // !GLOBAL_H
