/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#include <vector>
#include <functional>

#include "EngineBasis.h"
#include "GameObject.h"
#include "PlayerBase.h"
#include "Cube.h"
#include "CollisionEngine.h"

using namespace LightGameEngine::GeometricPrimitives;

namespace LightGameEngine
{
	class Engine
	{
	public:

		static void Init(int argc, char** argv, const std::string& windowName);
		static void Run();

		static void AddSceneObject(GameObject* obj);
		static void AddStageObject(GameObject* obj);

		static InputStatus* GetKeyboardStatus();

		static void SetPlayer(PlayerBase* obj);
		static void SetSkybox(Cube* skybox);

		static void SetPauseState(bool pause);
		static bool GetPauseState();

		static void RenderOverlayUICallback(std::function<void()> func);

	};
	
}

