#include "Teapot.h"

void Teapot::Draw()
{
	glColor3ub(125, 125, 125);
	glutSolidTeapot(50);
	//glutWireTeapot(100);
}
