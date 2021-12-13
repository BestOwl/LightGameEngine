#include "Engine.h"
#include "EngineUtil.h"

#include "TextureStore.h"
#include "Teapot.h"
#include "Humanoid.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "GunAK47.h"
#include "ControlPlayer.h"
#include "Terrain.h"

#include <sstream>

using namespace LightGameEngine;

BitmapFont* font;
GunAK47* gun;

void RenderOverlayUI()
{
	glColor4ub(255, 255, 255, 150);
	EngineUtil::DrawRasterString(font, 20, 800, "AK-47");
	std::stringstream ss = std::stringstream();
	ss << "Ammo: " << gun->GetCurrentAmmo() << " / " << gun->GetAmmoCapacity();
	EngineUtil::DrawRasterString(font, 20, 850, ss.str());

	TextureStore::AkOrtho->BindTexture();
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex2f(20, 650);

	glTexCoord2f(1, 0);
	glVertex2f(300, 650);

	glTexCoord2f(1, 1);
	glVertex2f(300, 750);
	
	glTexCoord2f(0, 1);
	glVertex2f(20, 750);

	glEnd();
	Texture::Unbind();
}

int main(int argc, char** argv) 
{
	Engine::Init(argc, argv, "Mission Possible");
	TextureStore::Init();
	font = EngineUtil::RasterStringSelectFont(36, ANSI_CHARSET, "Consolas Bold");

	Vector2 v = { 3.0f, 1.0f };
	Vector2 v2 = v.Rotate(180);

	Terrain* terrain = new Terrain(Vector3{ 0, 0, 0 }, -80.0, 80.f, 5.f, L"Assets/heightmap.png", TextureStore::Terrain);
	Engine::AddStageObject(terrain);

	ControlPlayer* player = new ControlPlayer(Vector3{ 0, 10, 0 });
	player->SetOnTerrain(terrain);
	Engine::SetPlayer(player);
	Engine::SetSkybox(new Cube(Vector3{ 0, 0, 0 }, 5000, TextureStore::Skybox));
	gun = (GunAK47*) player->GetHoldObject();

	//Engine::AddSceneObject(new Teapot(Vector3{ 5, 0, 0 }));

	HumanoidPlayer* bot =  new HumanoidPlayer{ Vector3{50, 50, 50} };
	bot->IsPhysicsEnabled = true;
	bot->SetOnTerrain(terrain);
	Engine::AddSceneObject(bot);

	//Engine::AddSceneObject(new Humanoid(Vector3{ 100, 100, 100 }));
	//Engine::AddSceneObject(new GeometricPrimitives::Sphere(Vector3{ -200, -200, -200 }, 50));
	//Engine::AddSceneObject(new GunAK47(Vector3{0, 10, 0}));
	//Engine::AddSceneObject(new Cube(Vector3{10, 10, 0}, 5, NULL));

	//Humanoid* human = new Humanoid(Vector3{ 0, 0, 0 });
	//human->SetShoulderYaw(HandSide::Left, 52.f);
	//human->SetShoulderPitch(HandSide::Left, -50.f);
	//human->SetElbowPitch(HandSide::Left, -50.f);

	//human->SetShoulderYaw(HandSide::Right, 40.f);
	//human->SetShoulderPitch(HandSide::Right, -10.f);
	//human->SetElbowYaw(HandSide::Right, 110.f);

	//GunAK47* gunAk = new GunAK47(Vector3{ 0,0, -0.1f });
	//gunAk->Rotation.z = -145.f;
	//gunAk->Rotation.x = -10.f;
	//gunAk->Rotation.y = -10.f;
	//human->SetHoldObject(HandSide::Right, gunAk);

	//Engine::AddSceneObject(human);

	//CubeTexture t(TextureStore::Terrain, TextureStore::Terrain, TextureStore::Terrain, TextureStore::Terrain, TextureStore::Terrain, TextureStore::Terrain);
	//Cube* testCube = new Cube(Vector3{ 5,0,0 }, 1, NULL);
	//Engine::AddSceneObject(testCube);

	Engine::RenderOverlayUICallback(std::bind(RenderOverlayUI));

	Engine::Run();
}

