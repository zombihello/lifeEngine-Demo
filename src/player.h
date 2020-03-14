#ifndef PLAYER_H
#define PLAYER_H
#include "engine/iconcmd.h"
#include "global.h"
#include "physics/ibody.h"
#include "physics/iphysicssystem.h"
#include "engine/iengine.h"
#include "engine/iwindow.h"


//TODO: add Update and fix move

class Player
{
public:
	Player();
	~Player();
	bool Initialize(le::IEngine* engine);
	
	void SetPosition( const le::Vector3D_t& Position );
	void Update();
	void Move( const le::Vector3D_t& OffsetMove );

	le::Vector3D_t  GetPosition(  );
	le::IBody* GetBody(  );
	le::ICamera* GetCamera(  );

	friend void  CMD_MoveLeft(le::UInt32_t CountArguments, const char** Arguments);
	friend void  CMD_MoveRight(le::UInt32_t CountArguments, const char** Arguments);
	friend void  CMD_MoveForward(le::UInt32_t CountArguments, const char** Arguments);
	friend void  CMD_MoveBackward(le::UInt32_t CountArguments, const char** Arguments);
private:
	bool isInitialize;
	le::IBody* body;
	le::ICamera* camera;

};
#endif// !PLAYER_H
