#include "player.h"
#include "physics/iphysicssystem.h"
Player::Player() :
	isInitialize( false )
{
}

Player::~Player()
{
	delete body;
	delete camera;
}

bool Player::Initialize(le::IEngine* engine)
{
	g_consoleSystem->PrintInfo(" isInitialize %i", isInitialize);
	if (isInitialize) return true;
	g_consoleSystem->PrintInfo("if isInitialize OK");
	
	body = (le::IBody*)g_physicsSystem->GetFactory()->Create(BODY_INTERFACE_VERSION);
	camera = (le::ICamera*)engine->GetFactory()->Create(CAMERA_INTERFACE_VERSION);

	le::UInt32_t		width, height;
	engine->GetWindow()->GetSize(width, height);

	camera->InitProjection_Perspective(75, (float)width / float(height), 0.1, 2500);

	le::ShapeCapsuleDecriptor capsule;
	capsule.height = 100;
	capsule.radius = 3;
	
	body->Initialize(capsule, 1.0, le::Vector3D_t(0, 0, 0), le::BODY_TYPE::BT_DYNAMIC);
	body->FreezeRotation( true, true, true );
	g_physicsSystem->AddBody(body);
	g_consoleSystem->PrintInfo("create body OK");
	isInitialize = true;
	return true;
}

le::Vector3D_t Player::GetPosition()
{
	return (le::Vector3D_t)body->GetPosition();
}


le::IBody* Player::GetBody()
{
	return body;
}

le::ICamera* Player::GetCamera()
{
	return camera;
}

void Player::SetPosition( const le::Vector3D_t& Position )
{
	body->SetPosition( Position );
}

void Player::Update()
{
	player->GetCamera()->RotateByMouse(g_inputSystem->GetMouseOffset(), g_inputSystem->GetMouseSensitivity());
	camera->SetPosition(body->GetPosition());
}

void Player::Move(const le::Vector3D_t& OffsetMove)
{
	body->ApplyImpulse( OffsetMove );
}



