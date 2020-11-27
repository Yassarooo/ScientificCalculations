#include "wheel.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


Wheel::Wheel(){
	wheelradius = 19.5;
	wheelspeed = 0;
	delta = 0;
}

double Wheel::getdelta(){
	return delta;
}

void Wheel::turnright(){
	delta -= 5;
	if (delta < -45)
		delta = -45;
}

void Wheel::turnleft(){
	delta += 5;
	if (delta > 45)
		delta = 45;
}

double Wheel::getwheelradius(){
	return wheelradius;
}

void Wheel::calwheelspeed(double rpm, double finalgear, double gear){
	wheelspeed = 2 * acos(-1) * rpm / (60 * finalgear * gear);
	wheelspeed *= wheelradius;
}

double Wheel::getwheelspeed(){
	return wheelspeed;
}

void Wheel::turntonormal(){
	if (delta > 0)
		delta -= 5;
	if (delta < 0)
		delta += 5;
}
