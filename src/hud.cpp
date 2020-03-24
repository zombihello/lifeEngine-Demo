//////////////////////////////////////////////////////////////////////////
//
//					*** Eliot: Episodic ***
//					Copyright (C) 2020
//
// Репозиторий:		https://github.com/zombihello/Eleot-Episodic/
// Авторы:			Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "engine/ifactory.h"

#include "global.h"
#include "hud.h"

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
HUD::HUD() :
	isInitialize( false ),
	camera( nullptr ),
	fontUI( nullptr ),
	versionEngine( nullptr )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
HUD::~HUD()
{
	if ( !isInitialize ) return;

	if ( camera->GetCountReferences() <= 1 )	camera->Release();
	else										camera->DecrementReference();

	if ( versionEngine->GetCountReferences() <= 1 )	versionEngine->Release();
	else											versionEngine->DecrementReference();

	g_resourceSystem->UnloadFont( "hud_font" );
	fontUI = nullptr;
}

// ------------------------------------------------------------------------------------ //
// Initialize
// ------------------------------------------------------------------------------------ //
void HUD::Initialize()
{
	if ( isInitialize )	return;

	// Initialize camera
	le::IFactory*			engineFactory = g_engine->GetFactory();
	camera = ( le::ICamera* ) engineFactory->Create( CAMERA_INTERFACE_VERSION );
	if ( !camera )			throw std::runtime_error( "le::ICamera interface version[" CAMERA_INTERFACE_VERSION "] not found in engine factory" );

	le::UInt32_t		windowWidth, windowHeight;
	g_window->GetSize( windowWidth, windowHeight );

	camera->IncrementReference();
	camera->InitProjection_Ortho( 0.0f, ( float ) windowWidth, 0.0f, ( float ) windowHeight, -150.f, 150.f );

	// Initialize text with version engine
	fontUI = g_resourceSystem->LoadFont( "hud_font", "fonts/ARIALBD.TTF" );
	if ( !fontUI )				throw std::runtime_error( "Font [fonts/ARIALBD.TTF] not found" );

	versionEngine = ( le::IText* ) engineFactory->Create( TEXT_INTERFACE_VERSION );
	if ( !versionEngine )		throw std::runtime_error( "le::IText interface version[" TEXT_INTERFACE_VERSION "] not found in engine factory" );

	versionEngine->IncrementReference();
	versionEngine->SetFont( fontUI );
	versionEngine->SetCharacterSize( 25 );
	versionEngine->SetPosition( le::Vector3D_t( 5, windowHeight - 25, 1 ) );
	versionEngine->SetText( "lifeEngine " LIFEENGINE_VERSION );
	isInitialize = true;
}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void HUD::Render()
{
	if ( !isInitialize ) return;

	g_studioRender->BeginScene( camera );
	g_studioRender->SubmitMesh( versionEngine->GetMesh(), versionEngine->GetTransformation() );
	g_studioRender->EndScene();
}
