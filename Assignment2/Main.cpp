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
#include "BotPlayer.h"
#include "CollisionEngine.h"

#include <sstream>

using namespace LightGameEngine;

BitmapFont* font;
BitmapFont* fontSmall;
GunAK47* gun;
ControlPlayer* player;
Terrain* terrain;

GLuint numberOfEnemies;
GLuint numberOfKills;

void BotBeenKilled()
{
	numberOfEnemies--;
	numberOfKills++;
}

void GenEnemyForce()
{
	numberOfEnemies++;
	Vector3 pos = player->GetPos();
	std::srand(time(NULL) + numberOfEnemies * 1000);
	GLfloat distance = std::rand() % 600;
	GLfloat yaw = std::rand() % 360;

	Vector3 v = EngineBasis::GetVectorFromYawAndPitch(yaw, 0);
	v.ScaleTo(distance);

	BotPlayer* bot = new BotPlayer(pos + v, player, std::bind(BotBeenKilled));
	bot->SetOnTerrain(terrain);
	Engine::AddSceneObject(bot);
}



void RenderOverlayUI()
{
	glColor4ub(255, 255, 255, 255);
	EngineUtil::DrawRasterString(font, 20, 800, "AK-47");
	std::stringstream ss = std::stringstream();
	ss << "Ammo: " << gun->GetCurrentAmmo() << " / " << gun->GetAmmoCapacity();
	EngineUtil::DrawRasterString(font, 20, 850, ss.str());

	glColor4ub(255, 155, 155, 255);
	EngineUtil::DrawRasterString(fontSmall, 20, 200, "Your Mission: ");
	EngineUtil::DrawRasterString(fontSmall, 20, 230, "Elimiate all enemies");
	EngineUtil::DrawRasterString(fontSmall, 20, 260, "Enemies killed: ");
	EngineUtil::DrawRasterString(fontSmall, 220, 260, std::to_string(numberOfKills));

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

void TimerTock()
{
	for (int i = numberOfEnemies; i < 10; i++)
	{
		GenEnemyForce();
	}
}

int main(int argc, char** argv) 
{
	Engine::Init(argc, argv, "Mission Possible");
	TextureStore::Init();
	font = EngineUtil::RasterStringSelectFont(36, ANSI_CHARSET, "Consolas Bold");
	fontSmall = EngineUtil::RasterStringSelectFont(24, ANSI_CHARSET, "Consolas Bold");

	terrain = new Terrain(Vector3{ 0, 0, 0 }, -80.0, 80.f, 5.f, L"Assets/heightmap.png", TextureStore::Terrain);
	Engine::AddStageObject(terrain);

	player = new ControlPlayer(Vector3{ 640.f, 200.f, 640.f });
	player->SetOnTerrain(terrain);
	Engine::SetPlayer(player);
	Engine::SetSkybox(new Cube(Vector3{ 0, 0, 0 }, 5000, TextureStore::Skybox));
	gun = (GunAK47*) player->GetHoldObject();

	//Engine::AddSceneObject(new Teapot(Vector3{ 5, 0, 0 }));

	//BotPlayer* bot =  new BotPlayer{ Vector3{5, 0.f, 5} , NULL};
	//bot->SetOnTerrain(terrain);
	//Engine::AddSceneObject(bot);

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
	Engine::TimerCallback(std::bind(TimerTock));

	Engine::Run();
}

