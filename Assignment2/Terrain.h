#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

class Terrain :
    public GameObject
{
public:
    Terrain(Vector3 initPos, GLfloat minY, GLfloat maxY, GLfloat squreSize, const std::wstring& heightMapPath, Texture* texture);
    ~Terrain();

    GLfloat GetHeight(GLfloat worldX, GLfloat worldZ);
    void GetTerrainBound(Vector3* minPos, Vector3* maxPos);

protected:
    GLfloat getMapHeight(GLuint mapX, GLuint mapY);
    Vector3 getNormal(GLuint mapX, GLuint mapY);

    GLfloat minY;
    GLfloat maxY;
    GLfloat squreSize;

    GLuint heightMapWidth = 0;
    GLuint heightMapHeight = 0;

    Mesh* mesh;
    GLuint** meshVertices;

    Texture* texture;

private:
    Mesh* genDebugMesh();
};

