#include "Cloud.h"

#include "NaiveEngineUtil.h"

void Cloud::Draw()
{
	glScalef(0.5, 0.5, 1);
	glColor3ub(250, 245, 245);

	DrawCircleArgs args = NaiveEngineUtil::GetDefaultDrawCircleArgs();
	args.xFactor = 1.8;
	NaiveEngineUtil::DrawCircle(0, 0, 30, &args);

	args.xFactor = 1.5;
	NaiveEngineUtil::DrawCircle(50, 15, 40, &args);

	glPushMatrix();
	glRotatef(15, 0, 0, 1);
	args.xFactor = 1.5;
	NaiveEngineUtil::DrawCircle(10, 40, 40, &args);
	glPopMatrix();

	args.xFactor = 1.2;
	NaiveEngineUtil::DrawCircle(-50, 5, 30, &args);


}
