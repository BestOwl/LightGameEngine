#include "Terrain.h"
#include "EngineUtil.h"

#include <iostream>
#include <vector>

const GLfloat MAX_COLOR = 256;

Terrain::Terrain(Vector3 initPos, GLfloat minY, GLfloat maxY, GLfloat squreSize, const std::wstring& heightMapPath, Texture* texture) : GameObject(initPos)
{
	GLubyte* buffer = EngineUtil::LoadImageFromFile(heightMapPath, 1, GUID_WICPixelFormat8bppGray, 
		&this->heightMapWidth, &this->heightMapHeight);
	
	this->meshVertices = new GLuint*[this->heightMapHeight];
	this->minY = minY;
	this->maxY = maxY;
	this->squreSize = squreSize;
	this->texture = texture;

	for (int row = 0; row < this->heightMapHeight; row++)
	{
		this->meshVertices[row] = new GLuint[this->heightMapWidth];
		for (GLint col = 0; col < this->heightMapWidth; col++)
		{
			this->meshVertices[row][col] = buffer[this->heightMapWidth * row + col];
		}
	}

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	for (int row = 0; row < this->heightMapHeight; row++)
	{
		for (int col = 0; col < this->heightMapWidth; col++)
		{
			vertices.push_back(Vertex{
				Vector3{(GLfloat)col * this->squreSize, getMapHeight(col, row), (GLfloat)row * this->squreSize},
				getNormal(col, row),
				Vector2{(GLfloat)col / ((GLfloat)this->heightMapWidth - 1.f), (GLfloat)row / ((GLfloat)this->heightMapHeight - 1.f)}
				});
		}
	}

	for (int row = 0; row < this->heightMapHeight - 1; row++)
	{
		for (int col = 0; col < this->heightMapWidth - 1; col++)
		{
			GLuint topLeft = row * this->heightMapWidth + col;
			GLuint topRight = topLeft + 1;
			GLuint bottomLeft = (row + 1) * this->heightMapWidth + col;
			GLuint bottomRight = bottomLeft + 1;

			indices.push_back(topLeft); 
			indices.push_back(bottomLeft);
			indices.push_back(topRight);

			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}

	this->mesh = new Mesh(Vector3{ 0,0,0 }, vertices, indices, this->texture);
	this->ChildrenObjects.push_back(mesh);

	//for (int i = 0; i < this->heightMapWidth * this->heightMapHeight; i++)
	//{
	//	//printf_s("%d %d %d %d\n", buffer[i * 4], buffer[i * 4 + 1], buffer[i * 4 + 2], buffer[i * 4 + 3]);
	//	printf_s("%u\n", buffer[i]);
	//	//std::cout << buffer[i * 4] << " " << buffer[i * 4 + 1] << " " << buffer[i * 4 + 2] << " " << buffer[i * 4 + 3] << std::endl;
	//}

	delete buffer;
}

Terrain::~Terrain()
{
	if (this->mesh)
	{
		delete this->mesh;
	}

	if (this->meshVertices)
	{
		for (int row = 0; row < this->heightMapHeight; row++)
		{
			delete this->meshVertices[row];
		}
		delete this->meshVertices;
	}
}

GLfloat barryCentric(Vector3 p1, Vector3 p2, Vector3 p3, Vector2 pos)
{
	GLfloat det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	GLfloat l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	GLfloat l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	GLfloat l3 = 1.f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

GLfloat Terrain::GetHeight(GLfloat worldX, GLfloat worldZ)
{
	Vector3 basePos = this->GetPos();
	GLfloat terrainX = worldX - basePos.x;
	GLfloat terrainZ = worldZ - basePos.z;

	GLuint mapX = floor(terrainX / this->squreSize);
	GLuint mapY = floor(terrainZ / this->squreSize);

	if (mapX < 0 || mapX >= this->heightMapWidth - 1 || mapY < 0 || mapY >= this->heightMapHeight - 1)
	{
		return 0.f;
	}

	GLfloat squreXoffset = fmodf(terrainX, this->squreSize) / this->squreSize;
	GLfloat squreZoffset = fmodf(terrainZ, this->squreSize) / this->squreSize;
	
	if (squreXoffset <= 1 - squreZoffset)
	{
		return barryCentric(Vector3{ 0, getMapHeight(mapX, mapY), 0 }, 
			Vector3{ 1, getMapHeight(mapX + 1, mapY), 0 }, 
			Vector3{ 0, getMapHeight(mapX, mapY + 1), 1 }, 
			Vector2{ squreXoffset, squreZoffset });
	}
	else
	{
		return barryCentric(Vector3{ 1, getMapHeight(mapX + 1, mapY), 0 }, 
			Vector3{ 1, getMapHeight(mapX + 1, mapY + 1), 1 }, 
			Vector3{ 0, getMapHeight(mapX, mapY + 1), 1 }, 
			Vector2{ squreXoffset, squreZoffset });
	}
}

void Terrain::GetTerrainBound(Vector3* minPos, Vector3* maxPos)
{
	*minPos = this->GetPos();
	minPos->y = this->minY;

	*maxPos = this->GetPos() + Vector3{ this->squreSize * this->heightMapWidth, 0, this->squreSize * this->heightMapHeight };
	maxPos->y = this->maxY;
}

GLfloat Terrain::getMapHeight(GLuint mapX, GLuint mapY)
{
	return this->minY + abs(this->maxY - this->minY) *  (GLfloat)this->meshVertices[mapY][mapX] / MAX_COLOR;
}

Vector3 Terrain::getNormal(GLuint mapX, GLuint mapY)
{
	if (mapX == 0 || mapX == this->heightMapWidth - 1 || mapY == 0 || mapY == this->heightMapHeight - 1)
	{
		return Vector3{ 0, 1, 0 };
	}

	GLfloat hLeft = getMapHeight(mapX - 1, mapY);
	GLfloat hRight = getMapHeight(mapX + 1, mapY);
	GLfloat hTop = getMapHeight(mapX, mapY + 1);
	GLfloat hBottom = getMapHeight(mapX, mapY - 1);
	Vector3 normal = { hLeft - hRight, 2.0f, hBottom - hTop };
	normal.ScaleTo(1);
	return normal;
}

Mesh* Terrain::genDebugMesh()
{
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex{
		Vector3{0, 0, 0},
		Vector3{0, 1, 0},
		Vector2{0, 0}
		});

	vertices.push_back(Vertex{
		Vector3{0, 0, 1},
		Vector3{0, 1, 0},
		Vector2{0, 1}
		});

	vertices.push_back(Vertex{
		Vector3{1, 0, 0},
		Vector3{0, 1, 0},
		Vector2{1, 0}
		});

	vertices.push_back(Vertex{
		Vector3{1, 0, 1},
		Vector3{0, 1, 0},
		Vector2{1, 1}
		});

	std::vector<GLuint> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	return new Mesh(Vector3{ 0,0,0 },vertices, indices, NULL);
}
