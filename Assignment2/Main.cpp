#include "Engine.h"
#include "Teapot.h"

using namespace LightGameEngine;

int main(int argc, char** argv) 
{
	Engine::Init(argc, argv);

	Engine::SetPlayer(new Player(-500, 0, 0));
	Engine::AddSceneObject(new Teapot(500, 0, 0));

	Engine::Run();
}

