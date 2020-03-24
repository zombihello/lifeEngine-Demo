//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "global.h"

le::IEngine*				g_engine = nullptr;
le::IConsoleSystem*			g_consoleSystem = nullptr;
le::IInputSystem*			g_inputSystem = nullptr;
le::IStudioRender*			g_studioRender = nullptr;
le::IResourceSystem*		g_resourceSystem = nullptr;
le::IWindow*				g_window = nullptr;
le::IPhysicsSystem*			g_physicsSystem = nullptr;

Game*						g_game = nullptr;
