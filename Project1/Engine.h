#ifndef Engine_H
#define Engine_H

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Engine{
public:
	double getrpm(double speed, double finalgear, double gear, double wheelradius);
	virtual double gettorque(double rpm) = 0;
};

class M9721 : public Engine{
	double gettorque(double rpm);
};

#endif Engine_H