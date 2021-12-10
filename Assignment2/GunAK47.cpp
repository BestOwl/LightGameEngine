#include "GunAK47.h"
#include "Cube.h"
#include "Cylinder.h"
#include "EngineUtil.h"

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

GunAK47::GunAK47(Vector3 initPos) : Gun(initPos)
{
	Cube* body = new Cube(Vector3{ 0, 0, 0 }, 1, NULL);
	body->Scale = Vector3{ 0.8, 0.1, 0.1 };
	this->ChildrenObjects.push_back(body);

	Cylinder* barrel = new Cylinder(Vector3{ 0.3f, -0.01f, 0 }, 0.015f, 0.5f, Vector3{ 1, 0, 0 });
	this->ChildrenObjects.push_back(barrel);

	Cylinder* sub_barrel = new Cylinder(Vector3{ 0.25f, 0.01f, 0 }, 0.015f, 0.25f, Vector3{ 1, 0, 0 });
	this->ChildrenObjects.push_back(sub_barrel);

	Cube* barrel_connector = new Cube(Vector3{ 0.6f, 0, 0 }, 0.1f, NULL);
	barrel_connector->Scale = Vector3{ 0.8f, 0.4f, 0.35f };
	this->ChildrenObjects.push_back(barrel_connector);
	
	MagAK47* mag = new MagAK47(Vector3{ 0.25f,0,0 });
	this->ChildrenObjects.push_back(mag);

	Cube* hold = new Cube(Vector3{ -0.25f, -0.12f, 0 }, 1, NULL);
	hold->Scale = Vector3{ 0.1f, 0.3f, 0.1f };
	hold->Rotation = Vector3{ 0, 0, -30 };
	this->ChildrenObjects.push_back(hold);
}

void GunAK47::Draw()
{
	//const Vector3 vertices[] = 
	//{
	//	Vector3{0,0,0},
	//	Vector3{0,1,0},
	//	Vector3{1,0,0},
	//	Vector3{2,0.5f,0},
	//	Vector3{2,0,0},

	//};

	//glBegin(GL_TRIANGLE_STRIP);
	//for (int i = 0; i < 4; i++)
	//{
	//	glVertex3fv((GLfloat*)&vertices[i]);
	//}
	//glEnd();
}

void MagAK47::Draw()
{
	DrawCircleArgs arg = EngineUtil::GetDefaultDrawCircleArgs();
	arg.startAngle = -90.f * M_PI / 180.f;
	arg.endAngle = 0.f;

	std::vector<Vector3> vertices = EngineUtil::GenCircleVertices3D(Vector3{ 0, 0, -0.04f }, 0.3f, Vector3{ 0, 0, 1 }, &arg);
	std::vector<Vector3> vertices2 = EngineUtil::GenCircleVertices3D(Vector3{ 0.025f, 0, -0.04f }, 0.2f, Vector3{ 0, 0, 1 }, &arg);

	const GLfloat magnetDepth = 0.08f;

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex3fv((GLfloat*)&vertices2[i]);
		glVertex3fv((GLfloat*)&vertices[i]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < vertices.size(); i++)
	{
		Vector3 vec = vertices2[i] + Vector3{ 0,0,magnetDepth };
		glVertex3fv((GLfloat*)&vec);

		vec = vertices[i] + Vector3{ 0,0,magnetDepth };
		glVertex3fv((GLfloat*)&vec);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (Vector3 v : vertices)
	{
		Vector3 vec = v + Vector3{ 0,0,magnetDepth };
		glVertex3fv((GLfloat*)&v);
		glVertex3fv((GLfloat*)&vec);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (Vector3 v : vertices2)
	{
		Vector3 vec = v + Vector3{ 0,0,magnetDepth };
		glVertex3fv((GLfloat*)&v);
		glVertex3fv((GLfloat*)&vec);
	}
	glEnd();
}
