#include "Engine.h"
#include "Teapot.h"
#include "CubeDemo.h"

using namespace LightGameEngine;

int main(int argc, char** argv) 
{
	Engine::Init(argc, argv);

	Engine::SetPlayer(new Player(Vector3{ -500, 0, 0}));
	Engine::AddSceneObject(new Teapot(Vector3{ 500, 0, 0 }));
	Engine::AddSceneObject(new CubeDemo(Vector3{ 25, 0, 0 }));

	Engine::Run();
}

