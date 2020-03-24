//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef HUD_H
#define HUD_H

#include "engine/icamera.h"
#include "engine/ifont.h"
#include "engine/itext.h"

#include "tsingleton.h"

//---------------------------------------------------------------------//

class HUD : public TSingleton< HUD >
{
public:
	// HUD
	HUD();
	~HUD();

	void			Initialize();
	void			Render();

private:
	bool				isInitialize;

	le::ICamera*		camera;
	le::IFont*			fontUI;
	le::IText*			versionEngine;
};

//---------------------------------------------------------------------//

#endif // !HUD_H
