#include "Engine.h"
#include "TextureStore.h"
#include "Teapot.h"
#include "Humanoid.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "GunAK47.h"
#include "ControlPlayer.h"

using namespace LightGameEngine;

int main(int argc, char** argv) 
{
	Engine::Init(argc, argv);
	TextureStore::Init();

	Engine::SetPlayer(new ControlPlayer(Vector3{ 0, 0, 0 }));
	Engine::SetSkybox(new Cube(Vector3{ 0, 0, 0 }, 5000, TextureStore::Skybox));

	Engine::AddSceneObject(new Teapot(Vector3{ 500, 0, 0 }));
	//Engine::AddSceneObject(new Humanoid(Vector3{ 100, 100, 100 }));
	//Engine::AddSceneObject(new GeometricPrimitives::Sphere(Vector3{ -200, -200, -200 }, 50));
	//Engine::AddSceneObject(new GunAK47(Vector3{0, 10, 0}));
	//Engine::AddSceneObject(new Cube(Vector3{10, 10, 0}, 5, NULL));

	Humanoid* human = new Humanoid(Vector3{ 0, 0, 0 });
	human->SetShoulderYaw(HandSide::Left, 52.f);
	human->SetShoulderPitch(HandSide::Left, -50.f);
	human->SetElbowPitch(HandSide::Left, -50.f);

	human->SetShoulderYaw(HandSide::Right, 40.f);
	human->SetShoulderPitch(HandSide::Right, -10.f);
	human->SetElbowYaw(HandSide::Right, 110.f);

	GunAK47* gunAk = new GunAK47(Vector3{ 0,0, -0.1f });
	gunAk->Rotation.z = -145.f;
	gunAk->Rotation.x = -10.f;
	gunAk->Rotation.y = -10.f;
	human->SetHoldObject(HandSide::Right, gunAk);

	Engine::AddSceneObject(human);

	Engine::Run();
}

