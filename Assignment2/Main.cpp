#include "Engine.h"
#include "Teapot.h"
#include "Humanoid.h"
#include "Cylinder.h"
#include "Sphere.h"

using namespace LightGameEngine;

int main(int argc, char** argv) 
{
	Engine::Init(argc, argv);

	Engine::SetPlayer(new Player(Vector3{ -500, 0, 0}));
	Engine::AddSceneObject(new Teapot(Vector3{ 500, 0, 0 }));
	Engine::AddSceneObject(new Humanoid(Vector3{ 100, 100, 100 }));
	Engine::AddSceneObject(new GeometricPrimitives::Cylinder(Vector3{ 0, 0, 0 }, 50, 50, Vector3{ 0, 1, 0 }, L""));
	Engine::AddSceneObject(new GeometricPrimitives::Sphere(Vector3{ -200, -200, -200 }, 50));

	Engine::Run();
}

