/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Mesh.h"

using namespace LightGameEngine::GeometricPrimitives;

Mesh::Mesh(Vector3 initPos, std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture* texture) : GameObject(initPos)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;

	setupMesh();
}

LightGameEngine::GeometricPrimitives::Mesh::~Mesh()
{
	if (this->ebo != NULL)
	{
		glDeleteBuffers(1, &this->ebo);
	}
	if (this->vbo != NULL)
	{
		glDeleteBuffers(1, &this->vbo);
	}
	if (this->vao != NULL)
	{
		glDeleteVertexArrays(1, &this->vao);
	}
}

void LightGameEngine::GeometricPrimitives::Mesh::Draw()
{
	if (this->texture != NULL)
	{
		this->texture->BindTexture();
	}

	glBindVertexArray(this->vao);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
	Texture::Unbind();
}

void LightGameEngine::GeometricPrimitives::Mesh::setupMesh()
{

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	if (this->texture != NULL)
	{
		this->texture->BindTexture();
	}

	// vertex pos
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);

	// vertex normal
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	
	// vertex texture coords
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}
