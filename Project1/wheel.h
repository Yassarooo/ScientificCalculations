#ifndef Wheel_H
#define Wheel_H

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Wheel{
private:
	double wheelradius;
	double wheelspeed;
	double delta;
public:
	Wheel();
	double getdelta();
	void turnright();
	void turnleft();
	double getwheelradius();
	void calwheelspeed(double rpm, double finalgear, double gear);
	double getwheelspeed();
	void turntonormal();
	void setWheelRadius(double u)
	{
		wheelradius = u;
	}
};

#endif Wheel_H