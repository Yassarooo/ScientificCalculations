#include "Engine.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

double Engine::getrpm(double speed, double finalgear, double gear, double wheelradius){
	double rpm = speed * finalgear * gear * 3600 / (wheelradius * 2 * acos(-1));
	rpm = abs(rpm);
	if (rpm < 1500)
		rpm = 1500;
	if (rpm>7500)
		rpm = 7500;
	return rpm;
}

double M9721::gettorque(double rpm){
	if (rpm >= 1500 && rpm <= 2500)
		return 0.037*rpm + 136.5;
	if (rpm > 2500 && rpm <= 3000)
		return 229;
	if (rpm > 3000 && rpm <= 3500)
		return -0.014 * rpm + 217;
	if (rpm > 3500 && rpm <= 4500)
		return 0.029*rpm + 120.5;
	if (rpm > 4500 && rpm <= 6000)
		return 251;
	return -0.037*rpm + 473;
}
