//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef INPUT_H
#define INPUT_H

#include "tsingleton.h"

//---------------------------------------------------------------------//

enum BUTTON_TYPE
{
	BT_MOVE_FORWARD,
	BT_MOVE_BACKWARD,
	BT_MOVE_LEFT,
	BT_MOVE_RIGHT,
	BT_SPRINT,
	BT_JUMP,
	BT_FLASHLIGHT,
	BT_COUNT
};

//---------------------------------------------------------------------//

class Input : public TSingleton< Input >
{
public:
	// Input
	Input();
	~Input();

	void			Initialize();
	void			ClearButtonsState();

	bool			IsButtonDown( BUTTON_TYPE Type );
};

//---------------------------------------------------------------------//

#endif // !INPUT_H
