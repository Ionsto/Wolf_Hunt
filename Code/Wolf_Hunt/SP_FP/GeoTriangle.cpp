#include "GeoTriangle.h"
#include <GL\glew.h>
GeoTriangle::GeoTriangle()
{
	
}


GeoTriangle::~GeoTriangle()
{
}
void GeoTriangle::Render()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(0, 1);
	glEnd();
}