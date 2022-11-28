/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#include <vector>

#include "EngineBasis.h"
#include "GameObject.h"
#include "Texture.h"

using namespace LightGameEngine;

namespace LightGameEngine::GeometricPrimitives
{
	struct vertex_struct
	{
		Vector3 Pos;
		Vector3 Normal;
		Vector2 TexCoords;
	};
	typedef vertex_struct Vertex;

	class Mesh :
		public GameObject
	{
	public:
		Mesh(Vector3 initPos, std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture* texture);
		~Mesh();
		
		virtual void Draw() override;

	protected:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		Texture* texture;

	private:
		void setupMesh();

		GLuint vao;
		GLuint vbo;
		GLuint ebo;
	};
}
